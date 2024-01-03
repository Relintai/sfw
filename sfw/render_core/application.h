#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/int_types.h"
#include <stdio.h>

#include "object/object.h"
#include "object/reference.h"

#include "render_core/scene.h"

class AppWindow;
class InputEvent;

class Application : public Object {
	SFW_OBJECT(Application, Object);

public:
	bool running;
	int target_fps;

	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();

	uint64_t get_idle_frames() const {
		return _idle_frames;
	}

	void core_loop();
	void main_loop();

	_FORCE_INLINE_ void core_loop_static() {
		Application::get_singleton()->core_loop();
	}

	Application();
	virtual ~Application();

	Ref<Scene> scene;

	static Application *get_singleton();

	real_t frame_delta;

protected:
	virtual void _init_window();

	static Application *_instance;

	uint64_t _idle_frames;

	real_t _time_scale;
};

#endif // APPLICATION_H
