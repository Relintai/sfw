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

typedef struct audio_handle *audio_t;

audio_t audio_clip(const char *pathfile);
audio_t audio_stream(const char *pathfile);

int audio_play(audio_t s, int flags);
int audio_play_gain(audio_t a, int flags, float gain /*0*/);
int audio_play_gain_pitch(audio_t a, int flags, float gain, float pitch /*1*/);
int audio_play_gain_pitch_pan(audio_t a, int flags, float gain, float pitch, float pan /*0*/);
int audio_stop(audio_t a);
void audio_loop(audio_t a, bool loop);
bool audio_playing(audio_t a);

float audio_volume_clip(float gain); // set     fx volume if gain is in [0..1] range. returns current     fx volume in any case
float audio_volume_stream(float gain); // set    bgm volume if gain is in [0..1] range. returns current    bgm volume in any case
float audio_volume_master(float gain); // set master volume if gain is in [0..1] range. returns current master volume in any case

int audio_mute(int mute);
int audio_muted();

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

int audio_queue(const void *samples, int num_samples, int flags);

//--STRIP
#endif
//--STRIP
