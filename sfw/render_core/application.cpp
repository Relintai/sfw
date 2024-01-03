#include "render_core/application.h"

#include "core/math_defs.h"

#include "core/stime.h"
#include "render_core/input.h"
#include "render_core/window.h"

void Application::input_event(const Ref<InputEvent> &event) {
	scene->input_event(event);
}

void Application::update(float delta) {
	scene->update(delta);
}

void Application::render() {
	scene->render();

	//SDL_GL_SwapWindow(window);
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

Application::Application() {
	_instance = this;

	running = true;
	target_fps = 60;

	scene = NULL;

	frame_delta = 0;

    if (!Input::get_singleton()) {
        memnew(Input());
    }

	/*
	SDL_SetMainReady();

	int error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	if (error) {
		SDL_Log("SDL_Init fail: %s\n", SDL_GetError());

		running = false;
		return;
	}

#if defined(_WIN64) || defined(_WIN32)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

	window = SDL_CreateWindow("SDL + OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window) {
		SDL_Log("SDL_CreateWindow Failed! %s\n", SDL_GetError());

		running = false;

		return;
	}

	context = SDL_GL_CreateContext(window);

	#if defined(_WIN64) || defined(_WIN32)
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	#endif // defined

	printf("%s\n", glGetString(GL_VERSION));
	*/
}
Application::~Application() {
	//SDL_DestroyWindow(window);

	// window = NULL;

	//SDL_Quit();
}

Application *Application::get_singleton() {
	return _instance;
}

Application *Application::_instance = NULL;
