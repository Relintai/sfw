
#include "sfwl.h"

#include "audio.h"

int main(int argc, char **argv) {
	SFWCore::setup();

	AudioServer::initialize();

	AudioServerHandle ta = AudioServer::get_singleton()->load_clip("test.wav");
	AudioServerHandle tas = AudioServer::get_singleton()->load_stream("test.mp3");
	float timer = 0;

	while (true) {
		timer += 0.1;

		if (timer > 2) {
			timer -= 2;
			ERR_PRINT("Playing sound!");
			bool res = AudioServer::get_singleton()->play(ta);
			ERR_PRINT(String::bool_str(res));
			ERR_PRINT(String::bool_str(AudioServer::get_singleton()->is_playing(ta)));

			if (!AudioServer::get_singleton()->is_playing(tas)) {
				ERR_PRINT("Play Stream");

				bool res = AudioServer::get_singleton()->play(tas);
				ERR_PRINT(String::bool_str(res));
			}
		}

		SFWTime::sleep_ms(100);
	}

	AudioServer::destroy();

	SFWCore::cleanup();

	return 0;
}
