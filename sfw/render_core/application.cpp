//--STRIP
#include "render_core/application.h"

#include "core/math_defs.h"

#include "core/stime.h"
#include "render_core/input.h"
#include "render_core/input_map.h"
#include "render_core/window.h"

#include "core/sfw_core.h"
#include "object/core_string_names.h"
//--STRIP

void Application::input_event(const Ref<InputEvent> &event) {
	ERR_FAIL_COND(scene.is_null());

	scene->input_event(event);
}

void Application::update(float delta) {
	ERR_FAIL_COND(scene.is_null());

	scene->update(delta);
}

void Application::render() {
	ERR_FAIL_COND(scene.is_null());

	scene->render();
}

void Application::main_loop() {
	uint64_t start = STime::time_us();

	AppWindow *w = AppWindow::get_singleton();

	if (!w->frame_begin()) { // calls Application::main_loop()
		w->shutdown();
		return;
	}

	//handle input
	Input::get_singleton()->iteration(frame_delta);

	//update_world
	update(frame_delta);

	//render
	render();

	uint64_t end = STime::time_us();

	uint64_t elapsed_us = end - start;

	real_t elapsed_seconds = USEC_TO_SEC(elapsed_us);

	real_t tfps = 1.0 / static_cast<float>(target_fps);
	real_t remaining = tfps - elapsed_seconds;

	++_idle_frames;

	if (remaining > 0) {
		frame_delta = tfps;

		STime::sleep_us((double)SEC_TO_USEC(remaining));
	} else {
		frame_delta = elapsed_seconds;
	}

	frame_delta *= _time_scale;

	w->frame_end();
	w->frame_swap();
}

void Application::_init_window() {
	AppWindow::get_singleton()->create(100, 0);
}

Application::Application() {
	_instance = this;

	running = true;
	target_fps = 60;

	frame_delta = 0;

	_time_scale = 1;

	SFWCore::setup();

	// TODO Move these to a central place in core!

	CoreStringNames::create();

	// TODO add a helper static method
	memnew(AppWindow());
	memnew(InputMap());
	memnew(Input());
	Input::get_singleton()->set_main_loop(this);

	_init_window();
}
Application::~Application() {
	_instance = NULL;

	// TODO Move these to a central place in core!

	CoreStringNames::free();

	// TODO add a helper static method
	memdelete(AppWindow::get_singleton());
	memdelete(Input::get_singleton());
	memdelete(InputMap::get_singleton());

	SFWCore::cleanup();
}

Application *Application::get_singleton() {
	return _instance;
}

Application *Application::_instance = NULL;
