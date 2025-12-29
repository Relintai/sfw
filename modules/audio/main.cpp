
#include "sfw.h"

#include "audio.h"

class AudioTestApplication : public Application {
	SFW_OBJECT(AudioTestApplication, Application);

public:
	virtual void input_event(const Ref<InputEvent> &event) {
	}

	virtual void update(float delta) {
		timer += delta;

		if (timer > 2) {
			timer -= 2;
			ERR_PRINT("Playing sound!");
			int res = AudioServer::get_singleton()->play(ta, 0 | AudioServer::AUDIO_2CH | AudioServer::AUDIO_16 | AudioServer::AUDIO_22KHZ);
			ERR_PRINT(String::num(res));
			ERR_PRINT(String::bool_str(AudioServer::get_singleton()->is_playing(ta)));

			if (!AudioServer::get_singleton()->is_playing(tas)) {
				ERR_PRINT("Play Stream");

				int res = AudioServer::get_singleton()->play(tas, 0 | AudioServer::AUDIO_2CH | AudioServer::AUDIO_16 | AudioServer::AUDIO_22KHZ);
				ERR_PRINT(String::num(res));
			}
		}
	}

	virtual void render() {
	}

	AudioTestApplication() {
		Renderer::initialize();

		AudioServer::initialize();


		//AudioServer::get_singleton()->set_volume_clip(1);
		//AudioServer::get_singleton()->set_volume_stream(1);
		//AudioServer::get_singleton()->set_volume_master(1);

		ta = AudioServer::get_singleton()->load_clip("test.wav");
		tas = AudioServer::get_singleton()->load_stream("test.mp3");
		timer = 0;
	}

	~AudioTestApplication() {
		AudioServer::destroy();
		Renderer::destroy();
	}

	AudioServerHandle ta;
	AudioServerHandle tas;
	float timer;
};

int main(int argc, char **argv) {
	Application *application = memnew(AudioTestApplication());

	while (application->running) {
		application->main_loop();
	}

	memdelete(application);

	return 0;
}
