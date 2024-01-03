#ifndef INPUT_H
#define INPUT_H

/*************************************************************************/
/*  input.h                                                              */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "core/vector2i.h"
#include "object/object.h"
//#include "core/os/main_loop.h"
#include "core/rb_map.h"
#include "core/rb_set.h"
#include "core/thread_safe.h"
#include "object/psignal.h"
#include "object/reference.h"
#include "render_core/input_event.h"

class Application;
struct GLFWwindow;

class Input : public Object {
	SFW_OBJECT(Input, Object);

	_THREAD_SAFE_CLASS_

public:
	Signal joy_connection_changed_signal;

	enum MouseMode {
		MOUSE_MODE_VISIBLE,
		MOUSE_MODE_HIDDEN,
		MOUSE_MODE_CAPTURED
	};

#undef CursorShape
	enum CursorShape {
		CURSOR_ARROW,
		CURSOR_IBEAM,
		CURSOR_POINTING_HAND,
		CURSOR_CROSS,
		CURSOR_WAIT,
		CURSOR_BUSY,
		CURSOR_DRAG,
		CURSOR_CAN_DROP,
		CURSOR_FORBIDDEN,
		CURSOR_VSIZE,
		CURSOR_HSIZE,
		CURSOR_BDIAGSIZE,
		CURSOR_FDIAGSIZE,
		CURSOR_MOVE,
		CURSOR_VSPLIT,
		CURSOR_HSPLIT,
		CURSOR_HELP,
		CURSOR_MAX
	};

	enum HatMask {
		HAT_MASK_CENTER = 0,
		HAT_MASK_UP = 1,
		HAT_MASK_RIGHT = 2,
		HAT_MASK_DOWN = 4,
		HAT_MASK_LEFT = 8,
	};

	enum HatDir {
		HAT_UP,
		HAT_RIGHT,
		HAT_DOWN,
		HAT_LEFT,
		HAT_MAX,
	};

	enum {
		JOYPADS_MAX = 16,
	};

	static Input *get_singleton();

	void set_mouse_mode(MouseMode p_mode);
	MouseMode get_mouse_mode() const;

	virtual bool is_key_pressed(int p_scancode) const;
	virtual bool is_physical_key_pressed(int p_scancode) const;
	virtual bool is_mouse_button_pressed(int p_button) const;
	virtual bool is_action_pressed(const StringName &p_action, bool p_exact = false) const;
	virtual bool is_action_just_pressed(const StringName &p_action, bool p_exact = false) const;
	virtual bool is_action_just_released(const StringName &p_action, bool p_exact = false) const;
	virtual float get_action_strength(const StringName &p_action, bool p_exact = false) const;
	virtual float get_action_raw_strength(const StringName &p_action, bool p_exact = false) const;

	float get_axis(const StringName &p_negative_action, const StringName &p_positive_action) const;
	Vector2 get_vector(const StringName &p_negative_x, const StringName &p_positive_x, const StringName &p_negative_y, const StringName &p_positive_y, float p_deadzone = -1.0f) const;

	virtual Point2 get_mouse_position() const;
	virtual Point2 get_last_mouse_speed();
	virtual int get_mouse_button_mask() const;

	void set_mouse_position(const Point2 &p_posf);

	virtual void warp_mouse_position(const Vector2 &p_to);
	virtual Point2i warp_mouse_motion(const Ref<InputEventMouseMotion> &p_motion, const Rect2 &p_rect);

	virtual void action_press(const StringName &p_action, float p_strength = 1.f);
	virtual void action_release(const StringName &p_action);

	virtual CursorShape get_default_cursor_shape() const;
	virtual void set_default_cursor_shape(CursorShape p_shape);
	virtual CursorShape get_current_cursor_shape() const;
	virtual void set_custom_mouse_cursor(const Ref<Reference> &p_cursor, CursorShape p_shape = CURSOR_ARROW, const Vector2 &p_hotspot = Vector2());

	virtual void parse_input_event(const Ref<InputEvent> &p_event);

	virtual void flush_buffered_events();
	virtual bool is_using_input_buffering();
	virtual void set_use_input_buffering(bool p_enable);
	virtual bool is_using_accumulated_input();
	virtual void set_use_accumulated_input(bool p_enable);

	virtual void release_pressed_events();

	void set_main_loop(Application *p_main_loop);
	void iteration(real_t p_step);

	Input();

	//Called by AppWindow
	void _setup_window_callbacks();

protected:
	static int glfw_to_sfw_code(int glfw_code);

	unsigned int get_mouse_button_state(unsigned int p_button, int p_type);
	static void get_key_modifier_state(int mods, Ref<InputEventWithModifiers> state);

	static void GLFWkeyfunCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void GLFWcharfunCallback(GLFWwindow *window, unsigned int codepoint);
	static void GLFWcharmodsfunCallback(GLFWwindow *window, unsigned int codepoint, int mods);
	static void GLFWmousebuttonfunCallback(GLFWwindow *window, int button, int action, int mods);
	static void GLFWcursorposfunCallback(GLFWwindow *window, double xpos, double ypos);
	static void GLFWcursorenterfunCallback(GLFWwindow *window, int entered);
	static void GLFWscrollfunCallback(GLFWwindow *window, double xoffset, double yoffset);
	static void GLFWdropfunCallback(GLFWwindow *window, int path_count, const char *paths[]);
	static void GLFWjoystickfunCallback(int jid, int event);
	static void GLFWwindowfocusfunCallback(GLFWwindow *window, int focused);

protected:

	struct SpeedTrack {
		uint64_t last_tick;
		Vector2 speed;
		Vector2 accum;
		float accum_t;
		float min_ref_frame;
		float max_ref_frame;

		void update(const Vector2 &p_delta_p);
		void reset();
		SpeedTrack();
	};

	struct Action {
		uint64_t pressed_idle_frame;
		uint64_t released_idle_frame;
		bool pressed;
		bool exact;
		float strength;
		float raw_strength;

		Action() {
			pressed_idle_frame = UINT64_MAX;
			released_idle_frame = UINT64_MAX;
			pressed = false;
			exact = true;
			strength = 0.0f;
			raw_strength = 0.0f;
		}
	};

	void _parse_input_event_impl(const Ref<InputEvent> &p_event, bool p_is_emulated);

	static String _hex_str(uint8_t p_byte);

	List<Ref<InputEvent>> buffered_events;
	bool use_input_buffering;
	bool use_accumulated_input;

	int mouse_button_mask;

	RBSet<int> physical_keys_pressed;
	RBSet<int> keys_pressed;

	Vector2 mouse_pos;

	Application *main_loop;
	bool legacy_just_pressed_behavior;

	Point2 last_mouse_pos;
	bool last_mouse_pos_valid;
	Point2i last_click_pos;
	uint64_t last_click_ms;
	int last_click_button_index;
	uint32_t last_button_state;

	int last_key_modifier_state;

	bool window_has_focus;

	RBMap<StringName, Action> action_state;

	SpeedTrack mouse_speed_track;

	CursorShape default_shape;

	static Input *singleton;
};

#endif // INPUT_H
