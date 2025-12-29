
#define MINIAUDIO_IMPLEMENTATION // miniaudio
#define MA_NO_FLAC // miniaudio
#define STS_MIXER_IMPLEMENTATION // sts_mixer

#ifdef __APPLE__
#define MA_NO_RUNTIME_LINKING // miniaudio osx
#endif

#define REALLOC memrealloc

//--STRIP

#include "audio.h"

#include "3rd_jo_mp1.h"

#define get_bits stb_vorbis_get_bits
#define error stb_vorbis_error
#include "3rd_stb_vorbis.h"
#undef error
#undef DEBUG

#include "3rd_miniaudio.h"
#include "3rd_sts_mixer.h"

//--STRIP

// @fixme: really shutdown audio & related threads before quitting. ma_dr_wav crashes.

// encapsulate ma_dr_wav,ma_dr_mp3,stbvorbis and some buffer with the sts_mixer_stream_t
enum {
	UNK,
	WAV,
	OGG,
	MP1,
	MP3
};

typedef struct {
	int type;
	union {
		ma_dr_wav wav;
		stb_vorbis *ogg;
		void *opaque;
		ma_dr_mp3 mp3_;
	};
	sts_mixer_stream_t stream; // mixer stream
	union {
		int32_t data[4096 * 2]; // static sample buffer
		float dataf[4096 * 2];
	};
	bool rewind;
	bool loop;
	Vector<uint8_t> *vdata;
} mystream_t;

static void downsample_to_mono_flt(int channels, float *buffer, int samples) {
	if (channels > 1) {
		float *output = buffer;
		while (samples-- > 0) {
			float mix = 0;
			for (int i = 0; i < channels; ++i)
				mix += *buffer++;
			*output++ = (float)(mix / channels);
		}
	}
}
static void downsample_to_mono_s16(int channels, short *buffer, int samples) {
	if (channels > 1) {
		short *output = buffer;
		while (samples-- > 0) {
			float mix = 0;
			for (int i = 0; i < channels; ++i)
				mix += *buffer++;
			*output++ = (short)(mix / channels);
		}
	}
}

// the callback to refill the (stereo) stream data
static bool refill_stream(sts_mixer_sample_t *sample, void *userdata) {
	mystream_t *stream = (mystream_t *)userdata;
	switch (stream->type) {
		default:
			break;
		case WAV: {
			int sl = sample->length / 2; /*sample->channels*/
			;
			if (stream->rewind)
				stream->rewind = 0, ma_dr_wav_seek_to_pcm_frame(&stream->wav, 0);
			if (ma_dr_wav_read_pcm_frames_s16(&stream->wav, sl, (short *)stream->data) < (ma_uint64)sl) {
				ma_dr_wav_seek_to_pcm_frame(&stream->wav, 0);
				if (!stream->loop)
					return false;
			}
		} break;
		case MP3: {
			int sl = sample->length / 2; /*sample->channels*/
			;
			if (stream->rewind)
				stream->rewind = 0, ma_dr_mp3_seek_to_pcm_frame(&stream->mp3_, 0);
			if (ma_dr_mp3_read_pcm_frames_f32(&stream->mp3_, sl, stream->dataf) < (ma_uint64)sl) {
				ma_dr_mp3_seek_to_pcm_frame(&stream->mp3_, 0);
				if (!stream->loop)
					return false;
			}
		} break;
		case OGG: {
			stb_vorbis *ogg = (stb_vorbis *)stream->ogg;
			if (stream->rewind)
				stream->rewind = 0, stb_vorbis_seek(stream->ogg, 0);
			if (stb_vorbis_get_samples_short_interleaved(ogg, 2, (short *)stream->data, sample->length) == 0) {
				stb_vorbis_seek(stream->ogg, 0);
				if (!stream->loop)
					return false;
			}
		}
	}

	return true;
}
static void reset_stream(mystream_t *stream) {
	if (stream)
		memset(stream->data, 0, sizeof(stream->data)), stream->rewind = 1;
}

// load a (stereo) stream
static bool load_stream(mystream_t *stream, const String &filename) {
	FileAccess *fa = FileAccess::create_and_open(filename, FileAccess::READ);

	if (!fa) {
		return false;
	}

	stream->vdata = memnew(Vector<uint8_t>());
	stream->vdata->resize(fa->get_len());

	uint64_t read_len = fa->get_buffer(stream->vdata->ptrw(), stream->vdata->size());

	if (read_len != fa->get_len()) {
		ERR_PRINT("read_len != fa->get_len()?");
		return false;
	}

	int datalen = stream->vdata->size();
	const char *data = (const char *)stream->vdata->ptr();

	if (!data) {
		return false;
	}

	int error;
	//int HZ = 44100;
	stream->type = UNK;
	stream->loop = true;

	if (stream->type == UNK && (stream->ogg = stb_vorbis_open_memory((const unsigned char *)data, datalen, &error, NULL))) {
		stb_vorbis_info info = stb_vorbis_get_info(stream->ogg);
		if (info.channels != 2) {
			ERR_PRINT("cannot stream ogg file. stereo required.");
			goto end;
		} // @fixme: upsample
		stream->type = OGG;
		stream->stream.sample.frequency = info.sample_rate;
		stream->stream.sample.audio_format = STS_MIXER_SAMPLE_FORMAT_16;
	}
	if (stream->type == UNK && ma_dr_wav_init_memory(&stream->wav, data, (size_t)datalen, NULL)) {
		if (stream->wav.channels != 2) {
			ERR_PRINT("cannot stream wav file. stereo required.");
			goto end;
		} // @fixme: upsample
		stream->type = WAV;
		stream->stream.sample.frequency = stream->wav.sampleRate;
		stream->stream.sample.audio_format = STS_MIXER_SAMPLE_FORMAT_16;
	}

	if (stream->type == UNK) {
		//ma_dr_mp3_config mp3_cfg = { 2, HZ };

		if ((ma_dr_mp3_init_memory(&stream->mp3_, data, (size_t)datalen, NULL /*&mp3_cfg*/) != 0)) {
			stream->type = MP3;
			stream->stream.sample.frequency = stream->mp3_.sampleRate;
			stream->stream.sample.audio_format = STS_MIXER_SAMPLE_FORMAT_FLOAT;
		}
	}

	if (stream->type == UNK) {
		return false;
	}

end:;
	stream->stream.userdata = stream;
	stream->stream.callback = refill_stream;
	stream->stream.sample.length = sizeof(stream->data) / sizeof(stream->data[0]);
	stream->stream.sample.data = stream->data;
	refill_stream(&stream->stream.sample, stream);

	return true;
}

// load a (mono) sample
static bool load_sample(sts_mixer_sample_t *sample, const String &filename) {
	Error err;
	Vector<uint8_t> vdata = FileAccess::get_file_as_array(filename, &err);

	if (err != OK) {
		return false;
	}

	int datalen = vdata.size();
	const char *data = (const char *)vdata.ptr();

	if (!data) {
		return false;
	}

	int error;
	int channels = 0;

	if (!channels)
		for (ma_dr_wav w = { 0 }, *wav = &w; wav && ma_dr_wav_init_memory(wav, data, (size_t)datalen, NULL); wav = 0) {
			channels = wav->channels;
			sample->frequency = wav->sampleRate;
			sample->audio_format = STS_MIXER_SAMPLE_FORMAT_16;
			sample->length = wav->totalPCMFrameCount;
			sample->data = memrealloc(0, sample->length * sizeof(short) * channels);
			ma_dr_wav_read_pcm_frames_s16(wav, sample->length, (short *)sample->data);
			ma_dr_wav_uninit(wav);
		}
	if (!channels)
		for (stb_vorbis *ogg = stb_vorbis_open_memory((const unsigned char *)data, datalen, &error, NULL); ogg; ogg = 0) {
			stb_vorbis_info info = stb_vorbis_get_info(ogg);
			channels = info.channels;
			sample->frequency = info.sample_rate;
			sample->audio_format = STS_MIXER_SAMPLE_FORMAT_16;
			sample->length = (int)stb_vorbis_stream_length_in_samples(ogg);
			stb_vorbis_close(ogg);

			short *buffer;
			int sample_rate;
			stb_vorbis_decode_memory((const unsigned char *)data, datalen, &channels, &sample_rate, (short **)&buffer);
			sample->data = buffer;
		}
	ma_dr_mp3_config mp3_cfg = { 2, 44100 };
	ma_uint64 mp3_fc;
	if (!channels)
		for (short *fbuf = ma_dr_mp3_open_memory_and_read_pcm_frames_s16(data, (size_t)datalen, &mp3_cfg, &mp3_fc, NULL); fbuf; fbuf = 0) {
			channels = mp3_cfg.channels;
			sample->frequency = mp3_cfg.sampleRate;
			sample->audio_format = STS_MIXER_SAMPLE_FORMAT_16;
			sample->length = mp3_fc; //  / sizeof(float) / mp3_cfg.channels;
			sample->data = fbuf;
		}

	if (!channels) {
		short *output = 0;
		int outputSize, hz, mp1channels;
		bool ok = jo_read_mp1(data, datalen, &output, &outputSize, &hz, &mp1channels);
		if (ok) {
			channels = mp1channels;
			sample->frequency = hz;
			sample->audio_format = STS_MIXER_SAMPLE_FORMAT_16;
			sample->length = outputSize / sizeof(int16_t) / channels;
			sample->data = output; // REALLOC(0, sample->length * sizeof(int16_t) * channels );
			// memcpy( sample->data, output, outputSize );
		}
	}

	if (!channels) {
		return false;
	}

	if (channels > 1) {
		if (sample->audio_format == STS_MIXER_SAMPLE_FORMAT_FLOAT) {
			downsample_to_mono_flt(channels, (float *)sample->data, sample->length);
			sample->data = memrealloc(sample->data, sample->length * sizeof(float));
		} else if (sample->audio_format == STS_MIXER_SAMPLE_FORMAT_16) {
			downsample_to_mono_s16(channels, (short int *)sample->data, sample->length);
			sample->data = memrealloc(sample->data, sample->length * sizeof(short));
		} else {
			puts("error!"); // @fixme
		}
	}

	return true;
}

// -----------------------------------------------------------------------------

static ma_device device;
static ma_context context;
static sts_mixer_t mixer;

// This is the function that's used for sending more data to the device for playback.
static void audio_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
	int len = frameCount;
	sts_mixer_mix_audio(&mixer, pOutput, len / (sizeof(int32_t) / 4));
	(void)pDevice;
	(void)pInput;
	// return len / (sizeof(int32_t) / 4);
}

void AudioServer::audio_drop() {
	ma_device_stop(&device);
	ma_device_uninit(&device);
	ma_context_uninit(&context);
}

int AudioServer::audio_init(int flags) {
	// init sts_mixer
	sts_mixer_init(&mixer, 44100, STS_MIXER_SAMPLE_FORMAT_32);

	// The prioritization of backends can be controlled by the application. You need only specify the backends
	// you care about. If the context cannot be initialized for any of the specified backends ma_context_init()
	// will fail.
	ma_backend backends[] = {
#if 1
		ma_backend_wasapi, // Higest priority.
		ma_backend_dsound,
		ma_backend_winmm,
		ma_backend_coreaudio,
		ma_backend_pulseaudio,
		ma_backend_alsa,
		ma_backend_oss,
		ma_backend_jack,
		ma_backend_opensl,
		// ma_backend_webaudio,
		// ma_backend_openal,
		//ma_backend_sdl,
		ma_backend_null // Lowest priority.
#else
		// Highest priority
		ma_backend_wasapi, // WASAPI      |  Windows Vista+
		ma_backend_dsound, // DirectSound |  Windows XP+
		ma_backend_winmm, // WinMM       |  Windows XP+ (may work on older versions, but untested)
		ma_backend_coreaudio, // Core Audio  |  macOS, iOS
		ma_backend_pulseaudio, // PulseAudio  |  Cross Platform (disabled on Windows, BSD and Android)
		ma_backend_alsa, // ALSA        |  Linux
		ma_backend_oss, // OSS         |  FreeBSD
		ma_backend_jack, // JACK        |  Cross Platform (disabled on BSD and Android)
		ma_backend_opensl, // OpenSL ES   |  Android (API level 16+)
		ma_backend_webaudio, // Web Audio   |  Web (via Emscripten)
		ma_backend_sndio, // sndio       |  OpenBSD
		ma_backend_audio4, // audio(4)    |  NetBSD, OpenBSD
		ma_backend_aaudio, // AAudio      |  Android 8+
		ma_backend_custom, // Custom      |  Cross Platform
		ma_backend_null, // Null        |  Cross Platform (not used on Web)
	// Lowest priority
#endif
	};

	if (ma_context_init(backends, (int)(sizeof(backends) / sizeof(0 [backends])), NULL, &context) != MA_SUCCESS) {
		LOG_ERR("Failed to initialize audio context.");
		return false;
	}

	ma_device_config config = ma_device_config_init(ma_device_type_playback); // Or ma_device_type_capture or ma_device_type_duplex.
	config.playback.pDeviceID = NULL; // &myPlaybackDeviceID; // Or NULL for the default playback device.
	config.playback.format = ma_format_s32;
	config.playback.channels = 2;
	config.sampleRate = 44100;
	config.dataCallback = audio_callback;
	config.pUserData = NULL;

	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
		ERR_PRINT("Failed to open playback device.");
		ma_context_uninit(&context);
		return false;
	}

	(void)flags;
	ma_device_start(&device);
	return true;
}

typedef struct AudioServerSample {
	bool is_clip;
	bool is_stream;
	union {
		sts_mixer_sample_t clip;
		mystream_t stream;
	};
} AudioServerSample;

AudioServerHandle AudioServer::audio_clip(const String &pathfile) {
	AudioServerSample *a = memnew(AudioServerSample);
	memset(a, 0, sizeof(AudioServerSample));
	a->is_clip = load_sample(&a->clip, pathfile);
	audio_instances.push_back(a);
	return a;
}
AudioServerHandle AudioServer::audio_stream(const String &pathfile) {
	AudioServerSample *a = memnew(AudioServerSample);
	memset(a, 0, sizeof(AudioServerSample));
	a->is_stream = load_stream(&a->stream, pathfile);
	audio_instances.push_back(a);
	return a;
}

float AudioServer::audio_volume_clip(float gain) {
	if (gain >= 0 && gain <= 1)
		volume_clip = gain * gain;
	// patch all live clips
	for (int i = 0; i < STS_MIXER_VOICES; ++i) {
		if (mixer.voices[i].state != STS_MIXER_VOICE_STOPPED) // is_active?
			if (mixer.voices[i].sample) // is_sample?
				mixer.voices[i].gain = volume_clip;
	}
	return sqrt(volume_clip);
}

float AudioServer::audio_volume_stream(float gain) {
	if (gain >= 0 && gain <= 1)
		volume_stream = gain * gain;
	// patch all live streams
	for (int i = 0; i < STS_MIXER_VOICES; ++i) {
		if (mixer.voices[i].state != STS_MIXER_VOICE_STOPPED) // is_active?
			if (mixer.voices[i].stream) // is_stream?
				mixer.voices[i].gain = volume_stream;
	}
	return sqrt(volume_stream);
}

float AudioServer::audio_volume_master(float gain) {
	if (gain >= 0 && gain <= 1)
		volume_master = gain * gain;
	// patch global mixer
	mixer.gain = volume_master;
	return sqrt(volume_master);
}

int AudioServer::audio_mute(int mute) {
	static bool muted = 0;

	if (mute >= 0 && mute <= 1) {
		muted = mute;
	}

	return muted;
}

int AudioServer::audio_muted() {
	return audio_mute(-1);
}

int AudioServer::audio_play_gain_pitch_pan(AudioServerHandle a, int flags, float gain, float pitch, float pan) {
	if (audio_muted()) {
		return 1;
	}

	if (flags & AUDIO_IGNORE_MIXER_GAIN) {
		// do nothing, gain used as-is
	} else {
		// apply mixer gains on top
		gain += a->is_clip ? volume_clip : volume_stream;
	}

	if (flags & AUDIO_SINGLE_INSTANCE) {
		audio_stop(a);
	}

	// gain: [0..+1], pitch: (0..N], pan: [-1..+1]

	if (a->is_clip) {
		int voice = sts_mixer_play_sample(&mixer, &a->clip, gain, pitch, pan);
		if (voice == -1)
			return 0; // all voices busy
	}
	if (a->is_stream) {
		int voice = sts_mixer_play_stream(&mixer, &a->stream.stream, gain);
		if (voice == -1)
			return 0; // all voices busy
	}
	return 1;
}

int AudioServer::audio_play_gain_pitch(AudioServerHandle a, int flags, float gain, float pitch) {
	return audio_play_gain_pitch_pan(a, flags, gain, pitch, 0);
}

int AudioServer::audio_play_gain(AudioServerHandle a, int flags, float gain) {
	return audio_play_gain_pitch(a, flags, gain, 1.f);
}

int AudioServer::audio_play(AudioServerHandle a, int flags) {
	return audio_play_gain(a, flags & ~AUDIO_IGNORE_MIXER_GAIN, 0.f);
}

int AudioServer::audio_stop(AudioServerHandle a) {
	if (a->is_clip) {
		sts_mixer_stop_sample(&mixer, &a->clip);
	}
	if (a->is_stream) {
		sts_mixer_stop_stream(&mixer, &a->stream.stream);
		reset_stream(&a->stream);
	}
	return 1;
}

void AudioServer::audio_loop(AudioServerHandle a, bool loop) {
	if (a->is_stream) {
		a->stream.loop = loop;
	}
}

bool AudioServer::audio_playing(AudioServerHandle a) {
	if (a->is_clip) {
		return !sts_mixer_sample_stopped(&mixer, &a->clip);
	}
	if (a->is_stream) {
		return !sts_mixer_stream_stopped(&mixer, &a->stream.stream);
	}
	return false;
}

// -----------------------------------------------------------------------------
// audio queue

#ifndef AUDIO_QUEUE_BUFFERING_MS
#define AUDIO_QUEUE_BUFFERING_MS 50 // 10 // 100
#endif
#ifndef AUDIO_QUEUE_MAX
#define AUDIO_QUEUE_MAX 2048
#endif

typedef struct AudioQueueEntry {
	int cursor;
	int avail;
	unsigned flags;
	char data[0];
} AudioQueueEntry;

static bool audio_queue_callback(sts_mixer_sample_t *sample, void *userdata) {
	AudioServer *self = (AudioServer *)userdata;

	int sl = sample->length / 2; // 2 ch
	int bytes = sl * 2 * (sample->audio_format == STS_MIXER_SAMPLE_FORMAT_16 ? 2 : 4);
	char *dst = (char *)sample->data;

	static AudioQueueEntry *aq = 0;

	do {
		while (!aq) {
			aq = self->_get_next_in_queue();

			if (!aq) {
				SFWTime::sleep_ns(10);
			}
		}

		int len = aq->avail > bytes ? bytes : aq->avail;
		memcpy(dst, (char *)aq->data + aq->cursor, len);
		dst += len;
		bytes -= len;
		aq->cursor += len;
		aq->avail -= len;

		if (aq->avail <= 0) {
			memfree(aq); // @fixme: mattias' original thread_queue_consume() implementation crashes here on tcc+win because of a double free on same pointer. using mcmp for now
			aq = 0;
		}
	} while (bytes > 0);

	return 1;
}

AudioQueueEntry *AudioServer::_get_next_in_queue() {
	_queue_mutex.lock();

	if (_audio_queues.front()) {
		AudioQueueEntry *aq = _audio_queues.front()->get();
		_audio_queues.pop_front();
		_queue_mutex.unlock();
		return aq;
	}

	_queue_mutex.unlock();

	return NULL;
}

void AudioServer::audio_queue_clear() {
	sts_mixer_stop_voice(&mixer, audio_queue_voice);
	audio_queue_voice = -1;

	_queue_mutex.lock();
	_audio_queues.clear();
	_queue_mutex.unlock();
}

int AudioServer::audio_queue(const void *samples, int num_samples, int flags) {
	float gain = 1; // [0..1]
	//float pitch = 1; // (0..N]
	//float pan = 0; // [-1..1]

	int bits = flags & AUDIO_8 ? 8 : flags & (AUDIO_32 | AUDIO_FLOAT) ? 32
																	  : 16;
	int channels = flags & AUDIO_2CH ? 2 : 1;
	int bytes_per_sample = channels * (bits / 8);
	int bytes = num_samples * bytes_per_sample;

	static sts_mixer_stream_t q = { 0 };
	if (audio_queue_voice < 0) {
		void *reuse_ptr = q.sample.data;
		q = ((sts_mixer_stream_t){ 0 });
		q.sample.data = reuse_ptr;

		q.callback = audio_queue_callback;
		q.userdata = this;
		q.sample.frequency = flags & AUDIO_8KHZ ? 8000 : flags & AUDIO_11KHZ ? 11025
				: flags & AUDIO_44KHZ										 ? 44100
				: flags & AUDIO_32KHZ										 ? 32000
																			 : 22050;
		q.sample.audio_format = flags & AUDIO_FLOAT ? STS_MIXER_SAMPLE_FORMAT_FLOAT : STS_MIXER_SAMPLE_FORMAT_16;
		q.sample.length = q.sample.frequency / (1000 / AUDIO_QUEUE_BUFFERING_MS); // num_samples;
		int bytes = q.sample.length * 2 * (flags & AUDIO_FLOAT ? 4 : 2);
		q.sample.data = memset(memrealloc(q.sample.data, bytes), 0, bytes);
		audio_queue_voice = sts_mixer_play_stream(&mixer, &q, gain * 1.f);
		if (audio_queue_voice < 0)
			return 0;
	}

	AudioQueueEntry *aq = (AudioQueueEntry *)memalloc(sizeof(AudioQueueEntry) + (bytes << (channels == 1))); // dupe space if going to be converted from mono to stereo
	aq->cursor = 0;
	aq->avail = bytes;
	aq->flags = flags;
	if (!samples) {
		memset(aq->data, 0, bytes);
	} else {
		// @todo: convert from other source formats to target format in here: add AUDIO_8, AUDIO_32
		if (channels == 1) {
			// mixer accepts stereo samples only; so resample mono to stereo if needed
			for (int i = 0; i < num_samples; ++i) {
				memcpy((char *)aq->data + (i * 2 + 0) * bytes_per_sample, (char *)samples + i * bytes_per_sample, bytes_per_sample);
				memcpy((char *)aq->data + (i * 2 + 1) * bytes_per_sample, (char *)samples + i * bytes_per_sample, bytes_per_sample);
			}
		} else {
			memcpy(aq->data, samples, bytes);
		}
	}

	// SHould probably use semaphores eventually.
	while (true) {
		_queue_mutex.lock();

		if (_audio_queues.size() >= AUDIO_QUEUE_MAX) {
			_queue_mutex.unlock();
			SFWTime::sleep_ns(10);
			continue;
		}

		_audio_queues.push_back(aq);
		_queue_mutex.unlock();
		break;
	}

	return audio_queue_voice;
}

void AudioServer::create() {
	if (_singleton) {
		return;
	}

	memnew(AudioServer);
}
void AudioServer::destroy() {
	if (_singleton) {
		memdelete(_singleton);
	}
}

AudioServer::AudioServer() {
	_singleton = this;

	volume_clip = 1;
	volume_stream = 1;
	volume_master = 1;
	audio_queue_voice = -1;
}
AudioServer::~AudioServer() {
	audio_drop();

	for (List<AudioServerSample *>::Element *E = audio_instances.front(); E; E = E->next()) {
		if (E->get()->is_stream) {
			memdelete(E->get()->stream.vdata);
		}

		memdelete(E->get());
	}

	audio_instances.clear();

	_singleton = NULL;
}

AudioServer *AudioServer::_singleton = NULL;
