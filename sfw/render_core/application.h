#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/int_types.h"
#include <stdio.h>

#include "object/object.h"
#include "object/reference.h"

#include "render_core/scene.h"

class AppWindow;
class InputEvent;

class Application : Object {
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

	uint64_t get_physics_frames() const {
		return _physics_frames;
	}

	bool is_in_physics_frame() const {
		return _is_in_physics_frame;
	}

	void main_loop();

	Application();
	virtual ~Application();

	Scene *scene;

	AppWindow *window;

	static Application *get_singleton();

	double frame_delta;

protected:
	static Application *_instance;

	uint64_t _idle_frames;
	uint64_t _physics_frames;
	bool _is_in_physics_frame;
};

#endif // APPLICATION_H
