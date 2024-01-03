//-----------------------------------------------------------------------------
// fps locking

#include "render_core/window.h"

#define GLAD_GL_IMPLEMENTATION // glad
#include "render_core/3rd_glad.h"

#define _GLFW_IMPLEMENTATION // glfw337
#define GLFW_INCLUDE_NONE // glfw337

#ifdef __APPLE__
#define _GLFW_COCOA // glfw osx
#elif defined(_WIN32) || defined(_WIN64)
#define _GLFW_WIN32 // glfw win32
#else
#define _GLFW_X11 // glfw linux, also _GLFW_OSMESA or _GLFW_WAYLAND
#endif

#undef _GNU_SOURCE

#include "3rd_glfw3.h"
#undef timeGetTime
#undef Time

#include "core/error_macros.h"
#include "core/stime.h"
#include "core/ustring.h"
#include "core/vector4.h"
#include "render_core/application.h"
#include "render_core/input/input.h"

/*
static volatile float framerate = 0;
static volatile unsigned fps_active, timer_counter, loop_counter;
static int fps__timing_thread(void *arg) {
	int64_t ns_excess = 0;
	while (fps_active) {
		if (framerate <= 0) {
			loop_counter = timer_counter = 0;
			STime::sleep_ms(250);
		} else {
			timer_counter++;
			int64_t tt = (int64_t)(1e9 / (float)framerate) - ns_excess;
			uint64_t took = -STime::time_ns();
#if is(win32)
			timeBeginPeriod(1);
			Sleep(tt > 0 ? tt / 1e6 : 0);
#else
			sleep_ns((float)tt);
#endif
			took += time_ns();
			ns_excess = took - tt;
			if (ns_excess < 0)
				ns_excess = 0;
			//puts( strf("%lld", ns_excess) );
		}
	}
	fps_active = 1;

	(void)arg;
	return thread_exit(0), 0;
}
static void fps_locker(int on) {
	if (on) {
		// private threaded timer
		fps_active = 1, timer_counter = loop_counter = 0;
		thread_init(fps__timing_thread, 0, "fps__timing_thread()", 0);
	} else {
		fps_active = 0;
	}
}
// function that locks render to desired `framerate` framerate (in FPS).
// - assumes fps_locker() was enabled beforehand.
// - returns true if must render, else 0.
static int fps_wait() {
	if (framerate <= 0)
		return 1;
	if (!fps_active)
		return 1;

	// if we throttled too much, cpu idle wait
	while (fps_active && (loop_counter > timer_counter)) {
		//thread_yield();
		STime::sleep_ns(100);
	}

	// max auto frameskip is 10: ie, even if speed is low paint at least one frame every 10
	enum { maxframeskip = 10 };
	if (timer_counter > loop_counter + maxframeskip) {
		loop_counter = timer_counter;
	}
	loop_counter++;

	// only draw if we are fast enough, otherwise skip the frame
	return loop_counter >= timer_counter;
}
static void AppWindow::vsync(float hz) {
	if (hz <= 0)
		return;
	do_once fps_locker(1);
	framerate = hz;
	fps_wait();
}
*/

//-----------------------------------------------------------------------------

#if 0 // deprecated
static void (*hooks[64])() = {0};
static void *userdatas[64] = {0};

bool AppWindow::hook(void (*func)(), void* user) {
    unhook( func );
    for( int i = 0; i < 64; ++i ) {
        if( !hooks[i] ) {
            hooks[i] = func;
            userdatas[i] = user;
            return true;
        }
    }
    return false;
}
void AppWindow::unhook(void (*func)()) {
    for( int i = 0; i < 64; ++i ) {
        if(hooks[i] == func) {
            hooks[i] = 0;
            userdatas[i] = 0;
        }
    }
}
#endif

// -----------------------------------------------------------------------------
// glfw

void AppWindow::glfw_error_callback(int error, const char *description) {
#ifdef __APPLE__
	if (error == 65544)
		return; // whitelisted
#endif

	CRASH_MSG(String(description) + " (error " + String::num(error) + ")");
}

void AppWindow::glfw_quit(void) {
	glfwTerminate();
}

void AppWindow::glfw_init() {
	glfwSetErrorCallback(glfw_error_callback);
	int ok = glfwInit();

	CRASH_COND(!ok);

	atexit(glfw_quit); //glfwTerminate);
}

void AppWindow::drop_callback(GLFWwindow *window, int count, const char **paths) {
}

void AppWindow::window_hints(unsigned flags) {
#ifdef __APPLE__
	//glfwInitHint( GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE );
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE); // @todo: remove silicon mac M1 hack
//glfwWindowHint( GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_FALSE );
//glfwWindowHint( GLFW_COCOA_MENUBAR, GLFW_FALSE );
#endif

#ifdef __APPLE__
	/* We need to explicitly ask for a 3.2 context on OS X */
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // osx
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); // osx, 2:#version150,3:330
#else
	// Compute shaders need 4.5 otherwise. But...
	// According to the GLFW docs, the context version hint acts as a minimum version.
	// i.e, the context you actually get may be a higher or highest version (which is usually the case)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //osx
#endif
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //osx+ems
	glfwWindowHint(GLFW_STENCIL_BITS, 8); //osx
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//according to the documentation, it must be GLFW_OPENGL_ANY_PROFILE.
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

	/*
	#if defined(_WIN64) || defined(_WIN32)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	#else
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	#endif
	*/

	//glfwWindowHint( GLFW_RED_BITS, 8 );
	//glfwWindowHint( GLFW_GREEN_BITS, 8 );
	//glfwWindowHint( GLFW_BLUE_BITS, 8 );
	//glfwWindowHint( GLFW_ALPHA_BITS, 8 );
	//glfwWindowHint( GLFW_DEPTH_BITS, 24 );

	//glfwWindowHint(GLFW_AUX_BUFFERS, Nth);
	//glfwWindowHint(GLFW_STEREO, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Prevent fullscreen window minimize on focus loss
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

	// Fix SRGB on intels
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	// glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // makes it non-resizable
	//if(flags & WINDOW_MSAA2) glfwWindowHint(GLFW_SAMPLES, 2); // x2 AA
	//if(flags & WINDOW_MSAA4) glfwWindowHint(GLFW_SAMPLES, 4); // x4 AA
	//if(flags & WINDOW_MSAA8) glfwWindowHint(GLFW_SAMPLES, 8); // x8 AA

	AppWindow::get_singleton()->_window_flags = flags;
}

void AppWindow::glNewFrame() {
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
	//glfwGetWindowSize(window, &w, &h);
	glfwGetFramebufferSize(_window, &w, &h);
	//printf("%dx%d\n", w, h);
#endif

	AppWindow::get_singleton()->width = w;
	AppWindow::get_singleton()->height = h;

	// blending defaults
	glEnable(GL_BLEND);

	// culling defaults
	//  glEnable(GL_CULL_FACE);
	//  glCullFace(GL_BACK);
	//  glFrontFace(GL_CCW);

	// depth-testing defaults
	glEnable(GL_DEPTH_TEST);
	//  glDepthFunc(GL_LESS);

	// depth-writing defaults
	//  glDepthMask(GL_TRUE);

	// seamless cubemaps
	//  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glViewport(0, 0, width, height);

	// GLfloat bgColor[4]; glGetFloatv(GL_COLOR_CLEAR_VALUE, bgColor);
	glClearColor(winbgcolor.r, winbgcolor.g, winbgcolor.b, has_transparent() ? 0 : winbgcolor.a); // @transparent
	//glClearColor(0.15,0.15,0.15,1);
	//glClearColor( clearColor.r, clearColor.g, clearColor.b, clearColor.a );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool AppWindow::create_from_handle(void *handle, float scale, unsigned int flags) {
	// abort run if any test suite failed in unit-test mode

	glfw_init();
	//fwk_init();

	if (!t)
		t = glfwGetTime();

#ifdef __EMSCRIPTEN__
	scale = 100.f;
#endif

	if (_fullscreen) {
		scale = 100;
	}

	scale = (scale < 1 ? scale * 100 : scale);

	bool FLAGS_FULLSCREEN = scale > 100;
	bool FLAGS_FULLSCREEN_DESKTOP = scale == 100;
	bool FLAGS_WINDOWED = scale < 100;
	bool FLAGS_TRANSPARENT = _transparent || (flags & WINDOW_TRANSPARENT);
	if (FLAGS_TRANSPARENT)
		FLAGS_FULLSCREEN = 0, FLAGS_FULLSCREEN_DESKTOP = 0, FLAGS_WINDOWED = 1;
	scale = (scale > 100 ? 100 : scale) / 100.f;
	int winWidth = get_canvas().x * scale;
	int winHeight = get_canvas().y * scale;

	window_hints(flags);

	GLFWmonitor *monitor = NULL;
#ifndef __EMSCRIPTEN__
	if (FLAGS_FULLSCREEN || FLAGS_FULLSCREEN_DESKTOP) {
		monitor = glfwGetPrimaryMonitor();
	}
	if (FLAGS_FULLSCREEN_DESKTOP) {
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		winWidth = mode->width;
		winHeight = mode->height;
	}
	if (FLAGS_WINDOWED) {
#ifndef __EMSCRIPTEN__
		if (FLAGS_TRANSPARENT) { // @transparent
			//glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE); // see through. requires undecorated
			//glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // always on top
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		}
		if (flags & WINDOW_BORDERLESS) {
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		}
#endif
		// windowed
		float ratio = (float)winWidth / (winHeight + !winHeight);
		if (flags & WINDOW_SQUARE)
			winWidth = winHeight = winWidth > winHeight ? winHeight : winWidth;
		//if( flags & WINDOW_LANDSCAPE ) if( winWidth < winHeight ) winHeight = winWidth * ratio;
		if (flags & WINDOW_PORTRAIT)
			if (winWidth > winHeight)
				winWidth = winHeight * (1.f / ratio);
	}
#endif

	_window = handle ? (GLFWwindow *)handle : glfwCreateWindow(winWidth, winHeight, "", monitor, NULL);

	ERR_FAIL_COND_V_MSG(!_window, false, "GLFW Window creation failed");

	glfwGetFramebufferSize(_window, &w, &h); //glfwGetWindowSize(window, &w, &h);

	if (flags & WINDOW_FIXED) { // disable resizing
		glfwSetWindowSizeLimits(_window, w, h, w, h);
	}
	if (flags & (WINDOW_SQUARE | WINDOW_PORTRAIT | WINDOW_LANDSCAPE | WINDOW_ASPECT)) { // keep aspect ratio
		aspect_lock(w, h);
	}

#ifndef __EMSCRIPTEN__
	if (FLAGS_WINDOWED) {
		// center window
		monitor = monitor ? monitor : glfwGetPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);

		int area_width = mode->width, area_height = mode->height;
		glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &area_width, &area_height);
		glfwSetWindowPos(_window, xpos = xpos + (area_width - winWidth) / 2, ypos = ypos + (area_height - winHeight) / 2);
		//printf("%dx%d @(%d,%d) [res:%dx%d]\n", winWidth, winHeight, xpos,ypos, area_width, area_height );

		wprev = w, hprev = h;
		xprev = xpos, yprev = ypos;
	}
#endif

	glfwMakeContextCurrent(_window);

#ifdef __EMSCRIPTEN__
	if (FLAGS_FULLSCREEN)
		fullscreen(1);
#else
	int gl_version = gladLoadGL(glfwGetProcAddress);
#endif

	//glDebugEnable();

	//glEnable(GL_TEXTURE_2D);

	// 0:disable vsync, 1:enable vsync, <0:adaptive (allow vsync when framerate is higher than syncrate and disable vsync when framerate drops below syncrate)
	//flags |= _vsync ? WINDOW_VSYNC : WINDOW_VSYNC_DISABLED;
	//flags |= _vsync_adaptive ? WINDOW_VSYNC_ADAPTIVE : 0;

	flags |= WINDOW_VSYNC_DISABLED;

	//int has_adaptive_vsync = glfwExtensionSupported("WGL_EXT_swap_control_tear") || glfwExtensionSupported("GLX_EXT_swap_control_tear") || //glfwExtensionSupported("EXT_swap_control_tear");
	//int wants_adaptive_vsync = (flags & WINDOW_VSYNC_ADAPTIVE);
	//int interval = has_adaptive_vsync && wants_adaptive_vsync ? -1 : (flags & WINDOW_VSYNC_DISABLED ? 0 : 1);
	//glfwSwapInterval(interval);

	//const GLFWvidmode *mode = glfwGetVideoMode(monitor ? monitor : glfwGetPrimaryMonitor());

	//PRINTF("Build version: %s\n", BUILD_VERSION);
	//PRINTF("Monitor: %s (%dHz, vsync=%d)\n", glfwGetMonitorName(monitor ? monitor : glfwGetPrimaryMonitor()), mode->refreshRate, interval);
	//PRINTF("GPU device: %s\n", glGetString(GL_RENDERER));
	//PRINTF("GPU driver: %s\n", glGetString(GL_VERSION));

#ifndef __EMSCRIPTEN__
	LOG_MSG("GPU OpenGL: " + String::num(GLAD_VERSION_MAJOR(gl_version)) + " " + String::num(GLAD_VERSION_MINOR(gl_version)));

	if (FLAGS_TRANSPARENT) { // @transparent
		glfwSetWindowAttrib(_window, GLFW_DECORATED, GLFW_FALSE); // @todo: is decorated an attrib or a hint?
		if (scale >= 1)
			glfwMaximizeWindow(_window);
	}
#endif

	width = get_width();
	height = get_height();

	// cursor(flags & WINDOW_NO_MOUSE ? false : true);
	glfwSetDropCallback(_window, drop_callback);

	// camera inits for fwk_pre_init() -> ddraw_flush() -> get_active_camera()
	// static camera_t cam = {0}; id44(cam.view); id44(cam.proj); extern camera_t *last_camera; last_camera = &cam;
	//fwk_pre_init();

	//fwk_post_init(mode->refreshRate);

	Input::get_singleton()->_setup_window_callbacks();

	return true;
}

bool AppWindow::create(float scale, unsigned int flags) {
	return create_from_handle(NULL, scale, flags);
}

char *AppWindow::get_stats() {
	static double num_frames = 0, begin = FLT_MAX, prev_frame = 0;

	double now = STime::time_ss();
	if (boot_time < 0)
		boot_time = now;

	if (begin > now) {
		begin = now;
		num_frames = 0;
	}
	if ((now - begin) >= 0.25f) {
		fps = num_frames * (1.f / (now - begin));
	}
	if ((now - begin) > 1) {
		begin = now + ((now - begin) - 1);
		num_frames = 0;
	}

	//const char *cmdline = app_cmdline();

	// @todo: print %used/%avail kib mem, %used/%avail objs as well
	static char buf[256];
	snprintf(buf, 256, "%s | boot %.2fs | %5.2ffps (%.2fms)",
			title,
			!boot_time ? now : boot_time,
			fps, (now - prev_frame) * 1000.f);
	//cmdline[0] ? " | " : "", cmdline[0] ? cmdline : "");

	prev_frame = now;
	++num_frames;

	return buf + strspn(buf, " ");
}

int AppWindow::frame_begin() {
	glfwPollEvents();

	if (glfwWindowShouldClose(_window)) {
		return 0;
	}

	glNewFrame();

	double now = paused ? t : glfwGetTime();
	dt = now - t;
	t = now;

	glfwSetWindowTitle(_window, title);

	return 1;
}

void AppWindow::frame_end() {
	// flush batching systems that need to be rendered before frame swapping. order matters.
	{
		/*
		font_goto(0, 0);
		touch_flush();
		sprite_flush();

		// flush all debugdraw calls before swap
		dd_ontop = 0;
		ddraw_flush();
		glClear(GL_DEPTH_BUFFER_BIT);
		dd_ontop = 1;
		ddraw_flush();

		ui_render();
		*/
	}
}

void AppWindow::frame_swap() {
	// glFinish();
	/*
#ifndef __EMSCRIPTEN__
	vsync(hz);
#endif
	*/
	glfwSwapBuffers(_window);
	// emscripten_webgl_commit_frame();
}

void AppWindow::shutdown() {
	loop_exit(); // finish emscripten loop automatically
}

int AppWindow::swap() {
	// end frame
	if (frame_count > 0) {
		frame_end();
		frame_swap();
	}

	++frame_count;

	// begin frame
	int ready = frame_begin();
	if (!ready) {
		shutdown();
		return 0;
	}
	return 1;
}

void AppWindow::resize() {
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
}

void AppWindow::loop_wrapper(void *loopArg) {
	AppWindow *w = AppWindow::get_singleton();
	if (w->frame_begin()) {
		w->resize();
		w->render_callback(loopArg);
		w->frame_end();
		w->frame_swap();
	} else {
		w->shutdown();
	}
}

void AppWindow::loop(void (*user_function)(void *loopArg), void *loopArg) {
#ifdef __EMSCRIPTEN__
	render_callback = user_function;
	emscripten_set_main_loop_arg(window_loop_wrapper, loopArg, 0, 1);
#else
	keep_running = true;
	while (keep_running)
		user_function(loopArg);
#endif /* __EMSCRIPTEN__ */
}

void AppWindow::loop_exit() {
#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#else
	keep_running = false;
#endif /* __EMSCRIPTEN__ */
}

Vector2 AppWindow::get_canvas() {
#ifdef __EMSCRIPTEN__
	int width = EM_ASM_INT_V(return canvas.width);
	int height = EM_ASM_INT_V(return canvas.height);
	return Vector2(width, height);
#else
	glfw_init();
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	CRASH_COND(!mode);
	return Vector2(mode->width, mode->height);
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
void AppWindow::set_title(const char *title_) {
	snprintf(title, 128, "%s", title_);
	if (!title[0])
		glfwSetWindowTitle(_window, title);
}
void AppWindow::set_color(unsigned color) {
	unsigned r = (color >> 0) & 255;
	unsigned g = (color >> 8) & 255;
	unsigned b = (color >> 16) & 255;
	unsigned a = (color >> 24) & 255;
	winbgcolor = Color(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

int AppWindow::has_icon() {
	return _has_icon;
}
void AppWindow::set_icon(const char *file_icon) {
	/*
	int len = 0;
	void *data = vfs_load(file_icon, &len);
	if (!data)
		data = file_read(file_icon), len = file_size(file_icon);

	if (data && len) {
		image_t img = image_from_mem(data, len, IMAGE_RGBA);
		if (img.w && img.h && img.pixels) {
			GLFWimage images[1];
			images[0].width = img.w;
			images[0].height = img.h;
			images[0].pixels = img.pixels;
			glfwSetWindowIcon(window, 1, images);
			has_icon = 1;
			return;
		}
	}
#if 0 // is(win32)
	HANDLE hIcon = LoadImageA(0, file_icon, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if( hIcon ) {
		HWND hWnd = glfwGetWin32Window(window);
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hWnd, WM_SETICON, ICON_BIG,   (LPARAM)hIcon);
		SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_BIG,   (LPARAM)hIcon);
		has_icon = 1;
		return;
	}
#endif
	*/
}
void *AppWindow::get_handle() {
	return _window;
}

Vector2 AppWindow::dpi() {
	Vector2 dpi = Vector2(1, 1);

#if !defined(__EMSCRIPTEN__) && !defined(__APPLE__) // @todo: remove silicon mac M1 hack`
	glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &dpi.x, &dpi.y);
#endif
	return dpi;
}

// -----------------------------------------------------------------------------
// fullscreen

GLFWmonitor *AppWindow::find_monitor(int wx, int wy) {
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();

	// find best monitor given current window coordinates. @todo: select by ocuppied window area inside each monitor instead.
	int num_monitors = 0;
	GLFWmonitor **monitors = glfwGetMonitors(&num_monitors);
#ifdef __EMSCRIPTEN__
	return *monitors;
#else
	for (int i = 0; i < num_monitors; ++i) {
		int mx = 0, my = 0, mw = 0, mh = 0;
		glfwGetMonitorWorkarea(monitors[i], &mx, &my, &mw, &mh);
		monitor = wx >= mx && wx <= (mx + mw) && wy >= my && wy <= (my + mh) ? monitors[i] : monitor;
	}
	return monitor;
#endif
}

#if 0 // to deprecate

void AppWindow::fullscreen(int enabled) {
    fullscreen = !!enabled;
#ifndef __EMSCRIPTEN__
    if( fullscreen ) {
        int wx = 0, wy = 0; glfwGetWindowPos(window, &wx, &wy);
        GLFWmonitor *monitor = find_monitor(wx, wy);

        wprev = w, hprev = h, xprev = wx, yprev = wy; // save window context for further restoring

        int width, height;
        glfwGetMonitorWorkarea(monitor, NULL, NULL, &width, &height);
        glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
    } else {
        glfwSetWindowMonitor(window, NULL, xpos, ypos, wprev, hprev, GLFW_DONT_CARE);
        glfwSetWindowPos(window, xprev, yprev);
    }
#endif
}
int AppWindow::has_fullscreen() {
    return fullscreen;
}

#else

int AppWindow::has_fullscreen() {
#ifdef __EMSCRIPTEN__
	EmscriptenFullscreenChangeEvent fsce;
	emscripten_get_fullscreen_status(&fsce);
	return !!fsce.isFullscreen;
#else
	return !!glfwGetWindowMonitor(_window);
#endif /* __EMSCRIPTEN__ */
}

void AppWindow::set_fullscreen(int enabled) {
	if (has_fullscreen() == !!enabled)
		return;

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

#if 0
    if( enabled ) {
        /*glfwGetWindowPos(g->window, &g->window_xpos, &g->window_ypos);*/
        glfwGetWindowSize(g->window, &g->width, &g->height);
        glfwSetWindowMonitor(g->window, glfwGetPrimaryMonitor(), 0, 0, g->width, g->height, GLFW_DONT_CARE);
    } else {
        glfwSetWindowMonitor(g->window, NULL, 0, 0, g->width, g->height, GLFW_DONT_CARE);
    }
#else
	if (enabled) {
		int wx = 0, wy = 0;
		glfwGetWindowPos(_window, &wx, &wy);
		GLFWmonitor *monitor = find_monitor(wx, wy);

		wprev = w, hprev = h, xprev = wx, yprev = wy; // save window context for further restoring

		int width, height;
		glfwGetMonitorWorkarea(monitor, NULL, NULL, &width, &height);
		glfwSetWindowMonitor(_window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
	} else {
		glfwSetWindowMonitor(_window, NULL, xpos, ypos, wprev, hprev, GLFW_DONT_CARE);
		glfwSetWindowPos(_window, xprev, yprev);
	}
#endif

#endif
}

#endif

void AppWindow::set_pause(int enabled) {
	paused = enabled;
}
int AppWindow::has_pause() {
	return paused;
}
void AppWindow::set_focus() {
	glfwFocusWindow(_window);
}
int AppWindow::has_focus() {
	return glfwGetWindowAttrib(_window, GLFW_FOCUSED);
}

void AppWindow::create_default_cursors() {
	if (_cursors_initialized) {
		return;
	}

	_cursors_initialized = true;

	unsigned int pixels[16 * 16] = { 0x01000000 }; // ABGR(le) glfw3 note: A(0x00) means 0xFF for some reason
	GLFWimage image = { 16, 16, (unsigned char *)pixels };
	GLFWcursor *empty;

	for (int x = 0; x < 16 * 16; ++x) {
		pixels[x] = pixels[0];
	}

	empty = glfwCreateCursor(&image, 0, 0);

	for (int i = 0; i < 7; ++i) {
		cursors[i] = i ? glfwCreateStandardCursor(cursor_enums[i]) : empty;
	}
}

void AppWindow::set_cursor_shape(unsigned mode) {
	_cursorshape = (mode &= 7);

	create_default_cursors();

	glfwSetCursor(_window, mode < 7 ? cursors[mode] : NULL);
}

void AppWindow::set_mouse_mode(MouseMode p_mode) {
	int im;

	if (p_mode == MOUSE_MODE_HIDDEN) {
		im = GLFW_CURSOR_HIDDEN;
	} else if (p_mode == MOUSE_MODE_CAPTURED) {
		im = GLFW_CURSOR_DISABLED;
	} else {
		//MOUSE_MODE_VISIBLE
		im = GLFW_CURSOR_NORMAL;
	}

	glfwSetInputMode(_window, GLFW_CURSOR, im);
}
AppWindow::MouseMode AppWindow::get_mouse_mode() const {
	int im = glfwGetInputMode(_window, GLFW_CURSOR);

	if (im == GLFW_CURSOR_HIDDEN) {
		return MOUSE_MODE_HIDDEN;
	} else if (im == GLFW_CURSOR_DISABLED) {
		return MOUSE_MODE_CAPTURED;
	}

	return MOUSE_MODE_VISIBLE;
}

void AppWindow::set_visible(int visible) {
	if (!_window)
		return;

	//if(window) (visible ? glfwRestoreWindow : glfwIconifyWindow)(window);
	(visible ? glfwShowWindow : glfwHideWindow)(_window);

// call glfwpollevents in linux to flush visiblity changes that would happen in next frame otherwise
#if defined(__linux__) || defined(__APPLE__)
	glfwPollEvents();
#endif
}
int AppWindow::has_visible() {
	return glfwGetWindowAttrib(_window, GLFW_VISIBLE);
}

double AppWindow::get_aspect() {
	return (double)w / (h + !h);
}
void AppWindow::aspect_lock(unsigned numer, unsigned denom) {
	if (!_window)
		return;
	if (numer * denom != 0) {
		glfwSetWindowAspectRatio(_window, numer, denom);
	} else {
		glfwSetWindowAspectRatio(_window, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
}
void AppWindow::aspect_unlock() {
	if (!_window)
		return;
	AppWindow::aspect_lock(0, 0);
}

void AppWindow::set_transparent(int enabled) {
#ifndef __EMSCRIPTEN__
	if (!has_fullscreen()) {
		if (enabled) {
			glfwSetWindowAttrib(_window, GLFW_DECORATED, GLFW_FALSE);
			//glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH , GLFW_TRUE);
			//glfwMaximizeWindow(window);
		} else {
			//glfwRestoreWindow(window);
			//glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH , GLFW_FALSE);
			glfwSetWindowAttrib(_window, GLFW_DECORATED, GLFW_TRUE);
		}
	}
#endif
}
int AppWindow::has_transparent() {
#ifndef __EMSCRIPTEN__
	return glfwGetWindowAttrib(_window, GLFW_DECORATED) != GLFW_TRUE;
#else
	return 0;
#endif
}

void AppWindow::set_maximize(int enabled) {
#ifndef __EMSCRIPTEN__
	if (!has_fullscreen()) {
		if (enabled) {
			glfwMaximizeWindow(_window);
		} else {
			glfwRestoreWindow(_window);
		}
	}
#endif
}
int AppWindow::has_maximize() {
#ifndef __EMSCRIPTEN__
	return glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) == GLFW_TRUE;
#else
	return 0;
#endif
}

const char *AppWindow::get_clipboard() {
	return glfwGetClipboardString(_window);
}
void AppWindow::set_clipboard(const char *text) {
	glfwSetClipboardString(_window, text);
}

double AppWindow::get_scale() { // ok? @testme
	float xscale, yscale;
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorContentScale(monitor, &xscale, &yscale);
	return MAX(xscale, yscale);
}

AppWindow *AppWindow::get_singleton() {
	return _singleton;
}

AppWindow::AppWindow() {
	_singleton = this;

	_window = NULL;

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
	locked_aspect_ratio = 0;
	title[0] = '\0';

	_has_icon = 0;

	_cursorshape = 1;

	render_callback = NULL;

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

	cursor_enums[0] = 0;
	cursor_enums[1] = GLFW_ARROW_CURSOR;
	cursor_enums[2] = GLFW_IBEAM_CURSOR;
	cursor_enums[3] = GLFW_HRESIZE_CURSOR;
	cursor_enums[4] = GLFW_VRESIZE_CURSOR;
	cursor_enums[5] = GLFW_HAND_CURSOR;
	cursor_enums[6] = GLFW_CROSSHAIR_CURSOR;
}
AppWindow::~AppWindow() {
	_singleton = NULL;
}

AppWindow *AppWindow::_singleton = NULL;
