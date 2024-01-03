#include "render_core/application.h"

#include "core/math_defs.h"

#include "core/stime.h"
#include "render_core/input/input.h"
#include "render_core/window.h"

#include "core/pool_vector.h"
#include "core/string_name.h"
#include "object/core_string_names.h"

void Application::input_event(const Ref<InputEvent> &event) {
	scene->input_event(event);
}

void Application::update(float delta) {
	scene->update(delta);
}

void Application::render() {
	scene->render();
}

void Application::core_loop() {
	AppWindow *w = AppWindow::get_singleton();

	if (w->frame_begin()) { // calls Application::main_loop()
		//w->resize();
		//w->render_callback(loopArg);
		w->frame_end();
		w->frame_swap();
	} else {
		w->shutdown();
	}
}

void Application::main_loop() {
	uint64_t start = STime::time_us();

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
}

void Application::_init_window() {
	AppWindow::get_singleton()->create(100, 0);
}

Application::Application() {
	_instance = this;

	running = true;
	target_fps = 60;

	frame_delta = 0;

	// TODO Move these to a central place in core!
	StringName::setup();
	MemoryPool::setup();
	CoreStringNames::create();

    // TODO add a helper static method
	memnew(AppWindow());

	if (!Input::get_singleton()) {
		memnew(Input());
	}

    _init_window();
}
Application::~Application() {
	_instance = NULL;

	// TODO Move these to a central place in core!
	StringName::cleanup();
	MemoryPool::cleanup();
	CoreStringNames::free();

    // TODO add a helper static method
	memdelete(AppWindow::get_singleton());
	memdelete(Input::get_singleton());
}

Application *Application::get_singleton() {
	return _instance;
}

Application *Application::_instance = NULL;
