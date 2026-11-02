//-----------------------------------------------------------------------------
// fps locking

//--STRIP
#include "render_core/app_window.h"

#ifdef __APPLE__

#include "render_core/3rd_glad.h"
//#include "3rd_glfw3.h"

#else

#define GLAD_GL_IMPLEMENTATION // glad
#include "render_core/3rd_glad.h"

#undef _GNU_SOURCE

#endif

//#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>

#include "core/error_macros.h"
#include "core/sfw_time.h"
#include "core/ustring.h"
#include "render_core/application.h"
#include "render_core/input.h"
#include "render_core/render_state.h"
//--STRIP

void AppWindow::setup_window_attributes(const uint32_t flags) {
#if 0
#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE); // @todo: remove silicon mac M1 hack
#endif
#endif

#if defined(__APPLE__)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	//according to the documentation, it must be GLFW_OPENGL_ANY_PROFILE.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_PROFILE_ES);
#elif defined(_WIN64) || defined(_WIN32)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	//according to the documentation, it must be GLFW_OPENGL_ANY_PROFILE.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_PROFILE_ES);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //osx+ems
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //osx

	// Defaults:
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE , 8 );
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8 );
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8 );
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8 );
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16 );
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);

	//glfwWindowHint(GLFW_AUX_BUFFERS, Nth);
	//glfwWindowHint(GLFW_STEREO, GL_TRUE);

	// Fix SRGB on intels. TODO check if needed with SDL
	// requests sRGB-capable visual if 1. Defaults to -1 ("don't care"). This is a request; GL drivers might not comply!
	//SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, GLFW_TRUE);

	// TODO likely needs SDL_GL_MULTISAMPLEBUFFERS

	if (flags & WINDOW_MSAA2)
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2); // x2 AA
	if (flags & WINDOW_MSAA4)
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // x4 AA
	if (flags & WINDOW_MSAA8)
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8); // x8 AA

	AppWindow::get_singleton()->_window_flags = flags;
}

void AppWindow::new_frame() {
	// @transparent debug
	// if( input_down(KEY_F1) ) transparent(window_has_transparent()^1);
	// if( input_down(KEY_F2) ) maximize(window_has_maximize()^1);
	// @transparent debug

#if 0 // #ifdef __EMSCRIPTEN__
    int canvasWidth, canvasHeight;
    emscripten_get_canvas_element_size("#canvas", &canvasWidth, &canvasHeight);
    w = canvasWidth;
    h = canvasHeight;
    //printf("%dx%d\n", w, h);
#else
	// Todo, test this with high DPI monitors
	SDL_GetWindowSizeInPixels(_window, &w, &h);
#endif

	AppWindow::get_singleton()->width = w;
	AppWindow::get_singleton()->height = h;

	glViewport(0, 0, width, height);
}

bool AppWindow::create_from_handle(void *handle, bool full_Screen, float canvas_scale, unsigned int flags, float window_scale) {
	//if (!t) {
	//	t = glfwGetTime();
	//}

#ifdef __EMSCRIPTEN__
	canvas_scale = 1.f;
#endif

	_fullscreen = full_Screen;

	bool FLAGS_FULLSCREEN = _fullscreen;
	bool FLAGS_FULLSCREEN_DESKTOP = _fullscreen && canvas_scale == 1;
	bool FLAGS_WINDOWED = !_fullscreen;
	bool FLAGS_TRANSPARENT = _transparent || (flags & WINDOW_TRANSPARENT);

	if (FLAGS_TRANSPARENT) {
		FLAGS_FULLSCREEN = false;
		FLAGS_FULLSCREEN_DESKTOP = false;
		FLAGS_WINDOWED = true;
	}

	int winWidth = get_canvas().x * window_scale;
	int winHeight = get_canvas().y * window_scale;

	setup_window_attributes(flags);

	SDL_DisplayID monitor = 0;

#ifndef __EMSCRIPTEN__
	if (FLAGS_FULLSCREEN || FLAGS_FULLSCREEN_DESKTOP) {
		monitor = SDL_GetPrimaryDisplay();
	}

	if (FLAGS_FULLSCREEN_DESKTOP) {
		const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(monitor);

		if (mode) {
			const SDL_PixelFormatDetails *fd = SDL_GetPixelFormatDetails(mode->format);

			if (fd) {
				SDL_GL_SetAttribute(SDL_GL_RED_SIZE, fd->Rbits);
				SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, fd->Gbits);
				SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, fd->Bbits);
				//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			}

			//dpi = mode->pixel_density;

			winWidth = mode->w;
			winHeight = mode->h;
		}
	}
#endif

	uint64_t window_flags = 0;

	if (FLAGS_WINDOWED) {
#ifndef __EMSCRIPTEN__
		if (FLAGS_TRANSPARENT) { // @transparent
			window_flags |= SDL_WINDOW_TRANSPARENT;
		}

		if (flags & WINDOW_BORDERLESS) {
			window_flags |= SDL_WINDOW_BORDERLESS;
		}
#endif

		// windowed
		float ratio = (float)winWidth / (winHeight + !winHeight);

		if (flags & WINDOW_SQUARE) {
			winWidth = winHeight = winWidth > winHeight ? winHeight : winWidth;
		}

		//if( flags & WINDOW_LANDSCAPE ) if( winWidth < winHeight ) winHeight = winWidth * ratio;
		if (flags & WINDOW_PORTRAIT) {
			if (winWidth > winHeight) {
				winWidth = winHeight * (1.f / ratio);
			}
		}
	}

	if (!(flags & WINDOW_FIXED)) {
		window_flags |= SDL_WINDOW_RESIZABLE;
	}

	// Only do this if opengl is enabled
	window_flags |= SDL_WINDOW_OPENGL;

	_window = SDL_CreateWindow("", winWidth, winHeight, window_flags);

	ERR_FAIL_COND_V_MSG(!_window, false, "SDL Window creation failed");

	// Only do this if opengl is enabled
	_context = SDL_GL_CreateContext(_window);

	// Todo, test this with high DPI monitors
	SDL_GetWindowSizeInPixels(_window, &w, &h);

#ifdef __EMSCRIPTEN__
	if (FLAGS_FULLSCREEN) {
		fullscreen(1);
	}
#else
	//int gl_version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	int gl_version = gladLoadGL(SDL_GL_GetProcAddress);
#endif

	// 0:disable vsync, 1:enable vsync, <0:adaptive (allow vsync when framerate is higher than syncrate and disable vsync when framerate drops below syncrate)
	//flags |= _vsync ? WINDOW_VSYNC : WINDOW_VSYNC_DISABLED;
	//flags |= _vsync_adaptive ? WINDOW_VSYNC_ADAPTIVE : 0;

	//flags |= WINDOW_VSYNC_DISABLED;

	//int has_adaptive_vsync = glfwExtensionSupported("WGL_EXT_swap_control_tear") || glfwExtensionSupported("GLX_EXT_swap_control_tear") || //glfwExtensionSupported("EXT_swap_control_tear");
	//int wants_adaptive_vsync = (flags & WINDOW_VSYNC_ADAPTIVE);
	//int interval = has_adaptive_vsync && wants_adaptive_vsync ? -1 : (flags & WINDOW_VSYNC_DISABLED ? 0 : 1);
	//glfwSwapInterval(interval);

	//const GLFWvidmode *mode = glfwGetVideoMode(monitor ? monitor : glfwGetPrimaryMonitor());

	//PRINTF("Build version: %s\n", BUILD_VERSION);
	//PRINTF("Monitor: %s (%dHz, vsync=%d)\n", glfwGetMonitorName(monitor ? monitor : glfwGetPrimaryMonitor()), mode->refreshRate, interval);
	//PRINTF("GPU device: %s\n", glGetString(GL_RENDERER));
	//PRINTF("GPU driver: %s\n", glGetString(GL_VERSION));

	LOG_MSG("GPU OpenGL: " + String::num(GLAD_VERSION_MAJOR(gl_version)) + " " + String::num(GLAD_VERSION_MINOR(gl_version)));

	width = get_width();
	height = get_height();

	RenderState::window_update_render_rect_size(width, height);

	if (!_title.empty()) {
		set_title(_title);
	}

	// cursor(flags & WINDOW_NO_MOUSE ? false : true);

	return true;
}

bool AppWindow::create(bool full_Screen, float canvas_scale, unsigned int flags, float window_scale) {
	return create_from_handle(NULL, full_Screen, canvas_scale, flags, window_scale);
}

int AppWindow::frame_begin() {
	Input::get_singleton()->poll_events();

	if (Input::get_singleton()->should_quit()) {
		return 0;
	}

	new_frame();

	return 1;
}

void AppWindow::frame_end() {
}

void AppWindow::frame_swap() {
	SDL_GL_SwapWindow(_window);
}

void AppWindow::reset_viewport() {
	glViewport(0, 0, width, height);
}

void AppWindow::resize() {
#if 0
#ifdef __EMSCRIPTEN__
	EM_ASM(canvas.canResize = 0);
	if (g->flags & WINDOW_FIXED)
		return;
	EM_ASM(canvas.canResize = 1);
	Vector2 size = canvas();
	if (size.x != last_canvas_size.x || size.y != last_canvas_size.y) {
		w = size.x;
		h = size.y;
		width = w;
		height = h;
		last_canvas_size = Vector2(w, h);
		emscripten_set_canvas_size(w, h);
	}
#endif /* __EMSCRIPTEN__ */
#endif
}

Vector2 AppWindow::get_canvas() {
#ifdef __EMSCRIPTEN__
	int width = EM_ASM_INT_V(return canvas.width);
	int height = EM_ASM_INT_V(return canvas.height);
	return Vector2(width, height);
#else
	Vector2 c = Vector2(800, 600); // Fallback

	SDL_DisplayID monitor = SDL_GetPrimaryDisplay();

	const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(monitor);

	if (mode) {
		c.x = mode->w;
		c.y = mode->h;
	}

	return c;
#endif /* __EMSCRIPTEN__ */
}

int AppWindow::get_width() {
	return w;
}
int AppWindow::get_height() {
	return h;
}
double AppWindow::get_time() {
	return t;
}
double AppWindow::get_delta() {
	return dt;
}

double AppWindow::get_fps() {
	return fps;
}
void AppWindow::fps_lock(float fps) {
	hz = fps;
}
void AppWindow::fps_unlock() {
	hz = 0;
}
double AppWindow::get_fps_target() {
	return hz;
}

uint64_t AppWindow::frame() {
	return frame_count;
}

String AppWindow::get_title() {
	return _title;
}

void AppWindow::set_title(const String &p_title) {
	_title = p_title;

	if (!_window) {
		return;
	}

	CharString cs = p_title.utf8();

	SDL_SetWindowTitle(_window, cs.get_data());
}

void *AppWindow::get_handle() {
	return _window;
}

Vector2 AppWindow::get_dpi() {
	Vector2 dpi = Vector2(1, 1);

#if !defined(__EMSCRIPTEN__) && !defined(__APPLE__) // @todo: remove silicon mac M1 hack`
	// TODO this should get the dpi of the display the window is on.
	SDL_DisplayID monitor = SDL_GetPrimaryDisplay();

	float d = SDL_GetDisplayContentScale(monitor);

	dpi.x = d;
	dpi.y = d;
#endif

	return dpi;
}

int AppWindow::has_fullscreen() {
#ifdef __EMSCRIPTEN__
	EmscriptenFullscreenChangeEvent fsce;
	emscripten_get_fullscreen_status(&fsce);
	return !!fsce.isFullscreen;
#else
	return _fullscreen;
#endif /* __EMSCRIPTEN__ */
}

void AppWindow::set_fullscreen(int enabled) {
	if (has_fullscreen() == enabled) {
		return;
	}

#ifdef __EMSCRIPTEN__

#if 0 // deprecated: crash
    if( enabled ) {
        emscripten_exit_soft_fullscreen();

        /* Workaround https://github.com/kripken/emscripten/issues/5124#issuecomment-292849872 */
        EM_ASM(JSEvents.inEventHandler = true);
        EM_ASM(JSEvents.currentEventHandler = {allowsDeferredCalls:true});

        EmscriptenFullscreenStrategy strategy = {0};
        strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH; // _ASPECT
        strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF; // _NONE _HIDEF
        strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT; // _NEAREST

        emscripten_request_fullscreen_strategy(NULL, EM_FALSE/*EM_TRUE*/, &strategy);
        //emscripten_enter_soft_fullscreen(NULL, &strategy);
    } else {
        emscripten_exit_fullscreen();
    }
#else
	if (enabled)
		EM_ASM(Module.requestFullscreen(1, 1));
	else
		EM_ASM(Module.exitFullscreen());
#endif

#else

	_fullscreen = enabled;

	SDL_SetWindowFullscreen(_window, enabled);

#endif
}

void AppWindow::create_default_cursors() {
	if (_cursors_initialized) {
		return;
	}

	_cursors_initialized = true;

	uint8_t pixels[16 * 16] = { 0x00 };
	SDL_Cursor *empty;

	for (int x = 0; x < 16 * 16; ++x) {
		pixels[x] = pixels[0];
	}

	empty = SDL_CreateCursor(pixels, pixels, 16, 16, 0, 0);

	cursors[0] = empty;
	cursors[1] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
	cursors[2] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT);
	cursors[3] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE);
	cursors[4] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NS_RESIZE);
	cursors[5] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	cursors[6] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
}

void AppWindow::set_cursor_shape(const CursorShapes mode) {
	_cursorshape = mode;

	create_default_cursors();

	SDL_SetCursor(cursors[static_cast<int>(mode)]);
}

void AppWindow::set_mouse_mode(MouseMode p_mode) {
	_mouse_mode = p_mode;

	if (p_mode == MOUSE_MODE_HIDDEN) {
		SDL_SetWindowRelativeMouseMode(_window, false);
		SDL_CaptureMouse(false);
		SDL_HideCursor();
	} else if (p_mode == MOUSE_MODE_CAPTURED) {
		SDL_CaptureMouse(true);
		SDL_HideCursor();
		SDL_SetWindowRelativeMouseMode(_window, true);
	} else {
		//MOUSE_MODE_VISIBLE
		SDL_SetWindowRelativeMouseMode(_window, false);
		SDL_CaptureMouse(false);
		SDL_ShowCursor();
	}
}
AppWindow::MouseMode AppWindow::get_mouse_mode() const {
	return _mouse_mode;
}

double AppWindow::get_aspect() {
	return (double)w / (h + !h);
}

const char *AppWindow::get_clipboard() {
#if 0
	return glfwGetClipboardString(_window);
#endif

	return NULL;
}
void AppWindow::set_clipboard(const char *text) {
#if 0
	glfwSetClipboardString(_window, text);
#endif
}

double AppWindow::get_scale() { // ok? @testme
#if 0
	float xscale, yscale;
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorContentScale(monitor, &xscale, &yscale);
	return MAX(xscale, yscale);
#endif

	return 0;
}

void *AppWindow::get_window_handle() {
	return _window;
}

AppWindow *AppWindow::get_singleton() {
	return _singleton;
}

AppWindow::AppWindow() {
	_singleton = this;

	_window = NULL;
	_context = NULL;

	boot_time = 0;

	w = 0;
	h = 0;
	xpos = 0;
	ypos = 0;
	paused = 0;
	fullscreen = 0;
	xprev = 0;
	yprev = 0;
	wprev = 0;
	hprev = 0;
	frame_count = 0;
	t = 0;
	dt = 0;
	fps = 0;
	hz = 0.00;
	title[0] = '\0';

	_cursorshape = CURSOR_HW_ARROW;

	width = 0;
	height = 0;
	keep_running = true;
	_window_flags = 0;

	_fullscreen = false;
	_transparent = false;
	_vsync = false;
	_vsync_adaptive = false;

	_cursors_initialized = false;

	for (int i = 0; i < 7; ++i) {
		cursors[i] = NULL;
	}

	// According to SDL Docs, subsystem inits are refcounted, so we should be okay with doing this
	bool success = SDL_InitSubSystem(SDL_INIT_VIDEO);

	if (!success) {
		ERR_PRINT("Failed to initialize SDL Video Subsystem! Error: " + String::utf8(SDL_GetError()));
	}
}
AppWindow::~AppWindow() {
	_singleton = NULL;

	for (int i = 0; i < 7; ++i) {
		if (cursors[i]) {
			SDL_DestroyCursor(cursors[i]);
		}
	}

	if (_context) {
		SDL_GL_DestroyContext(_context);
		_context = NULL;
	}

	if (_window) {
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

AppWindow *AppWindow::_singleton = NULL;
