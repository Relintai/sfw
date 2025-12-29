//--STRIP
#ifndef AUDIO_H
#define AUDIO_H
//--STRIP

#include "sfw.h"

// TODO would this work with sfwl?

// -----------------------------------------------------------------------------
// audio framework
// - rlyeh, public domain
//
// fixme: leaks, audio_delete
// @todo: audio_volume_fx, audio_volume_bgm, audio_volume_master instead?
// @todo: destroystream()    if( ss->type == WAV ) drwav_uninit(&ss->wav);
// @todo: destroystream()    if( ss->type == MOD ) jar_mod_unload(&ss->mod);
// @todo: destroystream()    if( ss->type == XM && ss->xm ) jar_xm_free_context(ss->xm);

// audio interface

struct AudioServerSample;
struct AudioQueueEntry;
typedef struct AudioServerSample *AudioServerHandle;

// implement free for handles

class AudioServer : public Object {
	SFW_OBJECT(AudioServer, Object);

public:
	enum AudioCustomQueueFlags {
		AUDIO_1CH = 0, // default
		AUDIO_2CH = 1,

		AUDIO_8 = 2,
		AUDIO_16 = 0, // default
		AUDIO_32 = 4,
		AUDIO_FLOAT = 8,

		AUDIO_8KHZ = 16,
		AUDIO_11KHZ = 32,
		AUDIO_22KHZ = 0, // default
		AUDIO_32KHZ = 64,
		AUDIO_44KHZ = 128,
	};

	// Clips
	AudioServerHandle load_clip(const String &pathfile);
	AudioServerHandle load_stream(const String &pathfile);

	void free(const AudioServerHandle p_handle);

	void audio_loop(AudioServerHandle a, bool loop);

	// Play
	bool play(AudioServerHandle a, bool single_instance = false, float gain = 1, float pitch = 1, float pan = 0, bool ignore_mixer_gain = true);

	int stop(AudioServerHandle a);

	bool is_playing(AudioServerHandle a);

	// Queue up custom samples
	int audio_queue(const void *samples, int num_samples, int queue_flags);

	// Volume
	// 0 .. 1 range
	float get_volume_clip() const;
	void set_volume_clip(float gain);

	float get_volume_stream() const;
	void set_volume_stream(float gain);

	float get_volume_master() const;
	void set_volume_master(float gain);

	bool is_muted() const;
	void set_mute(bool mute);

	static void initialize();
	static void destroy();

	static AudioServer *get_singleton() { return _singleton; }

	AudioServer();
	~AudioServer();

	AudioQueueEntry *_get_next_in_queue();

protected:
	void audio_queue_clear();

	float volume_clip;
	float volume_stream;
	float volume_master;
	int audio_queue_voice;
	bool _muted;

	List<AudioServerSample *> audio_instances;

	static AudioServer *_singleton;

	List<AudioQueueEntry *> _audio_queues;
	Mutex _queue_mutex;
};

//--STRIP
#endif
//--STRIP
