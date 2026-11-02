//--STRIP
#ifndef APP_WINDOW_H
#define APP_WINDOW_H
//--STRIP

// -----------------------------------------------------------------------------
// window framework
// - rlyeh, public domain
//
// @todo: cursor(ico);
// @todo: if WINDOW_PORTRAIT && exist portrait monitor, use that instead of primary one
// @todo: WINDOW_TRAY

//--STRIP
#include "core/color.h"
#include "core/int_types.h"
#include "core/vector2.h"
//--STRIP

struct SDL_Window;
struct SDL_GLContextState;
typedef struct SDL_GLContextState *SDL_GLContext;
struct SDL_Cursor;

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

	bool create(bool full_Screen, float canvas_scale, unsigned int flags, float window_scale = 0.8);
	bool create_from_handle(void *handle, bool full_Screen, float canvas_scale, unsigned int flags, float window_scale = 0.8);

	int frame_begin();
	void frame_end();
	void frame_swap();

	String get_title();
	void set_title(const String &p_title);

	Vector2 get_canvas();

	int get_width();
	int get_height();

	int has_fullscreen();
	void set_fullscreen(int enabled);

	bool maximize_window();
	bool minimize_window();
	bool restore_window();

	enum MouseMode {
		MOUSE_MODE_VISIBLE, //=GLFW_CURSOR_NORMAL
		MOUSE_MODE_HIDDEN, //=GLFW_CURSOR_HIDDEN
		MOUSE_MODE_CAPTURED //=GLFW_CURSOR_DISABLED
	};

	void set_mouse_mode(MouseMode p_mode);
	MouseMode get_mouse_mode() const;

	double get_aspect();

	void reset_viewport();

	Vector2 get_dpi();

	float get_display_content_scale();

	enum CursorShapes {
		CURSOR_NONE,
		CURSOR_HW_ARROW, // default
		CURSOR_HW_IBEAM, // i-beam text cursor
		CURSOR_HW_HDRAG, // horizontal drag/resize
		CURSOR_HW_VDRAG, // vertical drag/resize
		CURSOR_HW_HAND, // hand, clickable
		CURSOR_HW_CROSS, // crosshair
		CURSOR_SW_AUTO, // software cursor, ui driven. note: this is the only icon that may be recorded or snapshotted
	};

	void set_cursor_shape(const CursorShapes shape);

	bool has_clipboard_text();
	String get_clipboard_text();
	bool set_clipboard_text(const String &text);

	SDL_Window *get_sdl_window();
	SDL_GLContext get_sdl_gl_context();

	static AppWindow *get_singleton();

	AppWindow();
	~AppWindow();

protected:
	virtual void setup_window_attributes(const uint32_t flags);

	void resize();
	void new_frame();
	void create_default_cursors();

	static AppWindow *_singleton;

	SDL_Window *_window;
	SDL_GLContext _context;

	int w;
	int h;
	int xpos;
	int ypos;

	int xprev;
	int yprev;
	int wprev;
	int hprev;

	CursorShapes _cursorshape = CURSOR_HW_ARROW;

	Vector2 last_canvas_size;

	int width;
	int height;

	unsigned int _window_flags;

	bool _fullscreen;
	bool _transparent;

	String _title;

	MouseMode _mouse_mode;

	bool _cursors_initialized;
	SDL_Cursor *cursors[7];
};

//--STRIP
#endif
//--STRIP
