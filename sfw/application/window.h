// -----------------------------------------------------------------------------
// window framework
// - rlyeh, public domain
//
// @todo: cursor(ico);
// @todo: if WINDOW_PORTRAIT && exist portrait monitor, use that instead of primary one
// @todo: WINDOW_TRAY

#include "int_types.h"
#include "vector2.h"

class Window {
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

	bool create(float scale, unsigned flags);
	bool create_from_handle(void *handle, float scale, unsigned flags);
	void reload();

	int frame_begin();
	void frame_end();
	void frame_swap();
	int swap(); // single function that combines above functions (desktop only)

	void loop(void (*function)(void *loopArg), void *loopArg); // run main loop function continuously (emscripten only)
	void loop_exit(); // exit from main loop function (emscripten only)

	void title(const char *title);
	void color(unsigned color);
	Vector2 canvas();
	void *handle();
	char *stats();

	uint64_t frame();
	int width();
	int height();
	double time();
	double delta();

	// bool  hook(void (*func)(), void* userdata); // deprecated
	// void  unhook(void (*func)()); // deprecated

	void focus(); // window attribute using haz catz language for now
	int has_focus();
	void fullscreen(int enabled);
	int has_fullscreen();
	void cursor(int visible);
	int has_cursor();
	void pause(int paused);
	int has_pause();
	void visible(int visible);
	int has_visible();
	void maximize(int enabled);
	int has_maximize();
	void transparent(int enabled);
	int has_transparent();
	void icon(const char *file_icon);
	int has_icon();

	double aspect();
	void aspect_lock(unsigned numer, unsigned denom);
	void aspect_unlock();

	double fps();
	double fps_target();
	void fps_lock(float fps);
	void fps_unlock();

	void screenshot(const char *outfile_png); // , bool record_cursor
	int record(const char *outfile_mp4); // , bool record_cursor

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

	void cursor_shape(unsigned shape);

	const char *clipboard();
	void setclipboard(const char *text);

	static Window *get_singleton();

	Window();
	~Window();

protected:
	static Window *_singleton;

	struct GLFWwindow;

	GLFWwindow *window;
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
	Vector4 winbgcolor;
};