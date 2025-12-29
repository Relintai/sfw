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
	enum AUDIO_FLAGS {
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

		AUDIO_MIXER_GAIN = 0, // default
		AUDIO_IGNORE_MIXER_GAIN = 256,

		AUDIO_MULTIPLE_INSTANCES = 0, // default
		AUDIO_SINGLE_INSTANCE = 512,
	};

	// Api cleanups
	// getters, setters

	AudioServerHandle audio_clip(const String &pathfile);
	AudioServerHandle audio_stream(const String &pathfile);

	int audio_play(AudioServerHandle s, int flags);
	int audio_play_gain(AudioServerHandle a, int flags, float gain /*0*/);
	int audio_play_gain_pitch(AudioServerHandle a, int flags, float gain, float pitch /*1*/);
	int audio_play_gain_pitch_pan(AudioServerHandle a, int flags, float gain, float pitch, float pan /*0*/);
	int audio_stop(AudioServerHandle a);
	void audio_loop(AudioServerHandle a, bool loop);
	bool audio_playing(AudioServerHandle a);

	float audio_volume_clip(float gain); // set     fx volume if gain is in [0..1] range. returns current     fx volume in any case
	float audio_volume_stream(float gain); // set    bgm volume if gain is in [0..1] range. returns current    bgm volume in any case
	float audio_volume_master(float gain); // set master volume if gain is in [0..1] range. returns current master volume in any case

	int audio_mute(int mute);
	int audio_muted();

	int audio_queue(const void *samples, int num_samples, int flags);

	int audio_init(int flags);
	void audio_drop();

	// Should be initialize()
	static void create();
	static void destroy();

	static AudioServer *get_singleton() { return _singleton; }

	AudioServer();
	~AudioServer();

	// Make it protected
	AudioQueueEntry *_get_next_in_queue();

protected:
	void audio_queue_clear();

	float volume_clip;
	float volume_stream;
	float volume_master;
	int audio_queue_voice;

	List<AudioServerSample *> audio_instances;

	static AudioServer *_singleton;

	List<AudioQueueEntry *> _audio_queues;
	Mutex _queue_mutex;
};

//--STRIP
#endif
//--STRIP
