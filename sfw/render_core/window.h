#ifndef WINDOW_H
#define WINDOW_H

// -----------------------------------------------------------------------------
// window framework
// - rlyeh, public domain
//
// @todo: cursor(ico);
// @todo: if WINDOW_PORTRAIT && exist portrait monitor, use that instead of primary one
// @todo: WINDOW_TRAY

#include "color.h"
#include "int_types.h"
#include "vector2.h"

struct GLFWwindow;
struct GLFWcursor;
struct GLFWmonitor;

class AppWindow {
public:
	enum WINDOW_FLAGS {
		WINDOW_MSAA2 = 0x02,
		WINDOW_MSAA4 = 0x04,
		WINDOW_MSAA8 = 0x08,

		WINDOW_SQUARE = 0x20,
		WINDOW_PORTRAIT = 0x40,
		WINDOW_LANDSCAPE = 0x80,
		WINDOW_ASPECT = 0x100, // keep aspect
		WINDOW_FIXED = 0x200, // disable resizing
		WINDOW_TRANSPARENT = 0x400,
		WINDOW_BORDERLESS = 0x800,

		WINDOW_VSYNC = 0,
		WINDOW_VSYNC_ADAPTIVE = 0x1000,
		WINDOW_VSYNC_DISABLED = 0x2000,
	};

	bool create(float scale, unsigned int flags);
	bool create_from_handle(void *handle, float scale, unsigned int flags);

	int frame_begin();
	void frame_end();
	void frame_swap();
	int swap(); // single function that combines above functions (desktop only)

	void loop(void (*function)(void *loopArg), void *loopArg); // run main loop function continuously (emscripten only)
	void loop_exit(); // exit from main loop function (emscripten only)

	void set_title(const char *title);
	void set_color(unsigned color);
	Vector2 get_canvas();
	void *get_handle();
	char *get_stats();

	uint64_t frame();
	int get_width();
	int get_height();
	double get_time();
	double get_delta();

	// bool  hook(void (*func)(), void* userdata); // deprecated
	// void  unhook(void (*func)()); // deprecated

	void set_focus(); // window attribute using haz catz language for now
	int has_focus();
	void set_fullscreen(int enabled);
	int has_fullscreen();
	void set_cursor(int visible);
	int has_cursor();
	void set_pause(int paused);
	int has_pause();
	void set_visible(int visible);
	int has_visible();
	void set_maximize(int enabled);
	int has_maximize();
	void set_transparent(int enabled);
	int has_transparent();
	void set_icon(const char *file_icon);
	int has_icon();

	double get_aspect();
	void aspect_lock(unsigned numer, unsigned denom);
	void aspect_unlock();

	double get_fps();
	double get_fps_target();
	void fps_lock(float fps);
	void fps_unlock();

	void shutdown();

	Vector2 dpi();

	enum CURSOR_SHAPES {
		CURSOR_NONE,
		CURSOR_HW_ARROW, // default
		CURSOR_HW_IBEAM, // i-beam text cursor
		CURSOR_HW_HDRAG, // horizontal drag/resize
		CURSOR_HW_VDRAG, // vertical drag/resize
		CURSOR_HW_HAND, // hand, clickable
		CURSOR_HW_CROSS, // crosshair
		CURSOR_SW_AUTO, // software cursor, ui driven. note: this is the only icon that may be recorded or snapshotted
	};

	void set_cursor_shape(unsigned shape);

	const char *get_clipboard();
	void set_clipboard(const char *text);

	static AppWindow *get_singleton();

	AppWindow();
	~AppWindow();

protected:
	static void glfw_quit();
	static void glfw_init();
	static void glfw_error_callback(int error, const char *description);
	static void drop_callback(GLFWwindow *window, int count, const char **paths);
	static void window_hints(unsigned flags);
	GLFWmonitor *find_monitor(int wx, int wy);
	void resize();
	static void loop_wrapper(void *loopArg);
	void glNewFrame();
	double get_scale();
	void create_default_cursors();

	static AppWindow *_singleton;

	double boot_time;

	GLFWwindow *_window;
	int w;
	int h;
	int xpos;
	int ypos;
	int paused;
	int fullscreen;
	int xprev;
	int yprev;
	int wprev;
	int hprev;
	uint64_t frame_count;
	double t;
	double dt;
	double fps;
	double hz;
	char title[128];
	int locked_aspect_ratio;
	Color winbgcolor;
	int _has_icon;

	int _cursorshape = 1;

	void (*render_callback)(void *loopArg);
	Vector2 last_canvas_size;

	int width;
	int height;
	bool keep_running;
	unsigned int _window_flags;

	bool _fullscreen;
	bool _transparent;
	bool _vsync;
	bool _vsync_adaptive;

	bool _cursors_initialized;
	GLFWcursor *cursors[7];
	unsigned int cursor_enums[7];
};

#endif
