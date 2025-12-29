
#define MINIAUDIO_IMPLEMENTATION // miniaudio
#define MA_NO_FLAC // miniaudio
#define STS_MIXER_IMPLEMENTATION // sts_mixer

#ifdef __APPLE__
#define MA_NO_RUNTIME_LINKING // miniaudio osx
#endif

#define REALLOC memrealloc

#include "sfw_audio.h"

{{FILEINLINE:modules/audio/3rd_jo_mp1.h}}

#define get_bits stb_vorbis_get_bits
#define error stb_vorbis_error
{{FILEINLINE:modules/audio/3rd_stb_vorbis.h}}
#undef error
#undef DEBUG

{{FILEINLINE:modules/audio/3rd_miniaudio.h}}
{{FILEINLINE:modules/audio/3rd_sts_mixer.h}}

{{FILEINLINE:modules/audio/audio.cpp}}

