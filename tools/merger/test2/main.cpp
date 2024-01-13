
#include "sfw.h"

class GameApplication : public Application {
	SFW_OBJECT(GameApplication, Application);

public:
	virtual void input_event(const Ref<InputEvent> &event) {}
	virtual void update(float delta) {
		_font_pos.x += 500 * delta;
		if (_font_pos.x > 1800) {
			_font_pos.x = 0;
		}
	}
	virtual void render() {
		Renderer::get_singleton()->clear_screen(Color());
		Renderer::get_singleton()->camera_2d_projection_set_to_window();
		Renderer::get_singleton()->draw_text_2d("Test!", _font, _font_pos);
	}

	GameApplication() {
		_font.instance();
		_font->load_default(31.5);
		_font_pos = Vector2(0, 500);

		Renderer::initialize();
	}

	~GameApplication() {
		Renderer::destroy();
	}

	Vector2 _font_pos;
	Ref<Font> _font;
};

int main(int argc, char **argv) {
	Application *application = memnew(GameApplication());

	while (application->running) {
		application->main_loop();
	}

	memdelete(application);

	return 0;
}
