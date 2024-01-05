#ifndef APPLICATION_H
#define APPLICATION_H

//--STRIP
#include "core/int_types.h"
#include <stdio.h>

#include "object/object.h"
#include "object/reference.h"

#include "render_core/scene.h"
//--STRIP

class AppWindow;
class InputEvent;

class Application : public Object {
	SFW_OBJECT(Application, Object);

public:
	enum {
		NOTIFICATION_WM_MOUSE_ENTER = 1002,
		NOTIFICATION_WM_MOUSE_EXIT = 1003,
		NOTIFICATION_WM_FOCUS_IN = 1004,
		NOTIFICATION_WM_FOCUS_OUT = 1005,
		NOTIFICATION_WM_QUIT_REQUEST = 1006,
		NOTIFICATION_WM_GO_BACK_REQUEST = 1007,
		NOTIFICATION_WM_UNFOCUS_REQUEST = 1008,

		NOTIFICATION_APP_RESUMED = 1014,
		NOTIFICATION_APP_PAUSED = 1015,
	};

	bool running;
	int target_fps;

	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();

	uint64_t get_idle_frames() const {
		return _idle_frames;
	}

	void main_loop();

	_FORCE_INLINE_ void main_loop_static() {
		Application::get_singleton()->main_loop();
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
