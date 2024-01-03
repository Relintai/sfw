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
#include "render_core/input/input_event.h"

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
		MOUSE_MODE_CAPTURED,
		MOUSE_MODE_CONFINED
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
	virtual bool is_joy_button_pressed(int p_device, int p_button) const;
	virtual bool is_action_pressed(const StringName &p_action, bool p_exact = false) const;
	virtual bool is_action_just_pressed(const StringName &p_action, bool p_exact = false) const;
	virtual bool is_action_just_released(const StringName &p_action, bool p_exact = false) const;
	virtual float get_action_strength(const StringName &p_action, bool p_exact = false) const;
	virtual float get_action_raw_strength(const StringName &p_action, bool p_exact = false) const;

	float get_axis(const StringName &p_negative_action, const StringName &p_positive_action) const;
	Vector2 get_vector(const StringName &p_negative_x, const StringName &p_positive_x, const StringName &p_negative_y, const StringName &p_positive_y, float p_deadzone = -1.0f) const;

	virtual float get_joy_axis(int p_device, int p_axis) const;
	virtual String get_joy_name(int p_idx);
	virtual Array get_connected_joypads();
	virtual void joy_connection_changed(int p_idx, bool p_connected, String p_name, String p_guid);

	virtual Vector2 get_joy_vibration_strength(int p_device);
	virtual float get_joy_vibration_duration(int p_device);
	virtual uint64_t get_joy_vibration_timestamp(int p_device);

	virtual void add_joy_mapping(String p_mapping, bool p_update_existing = false);
	virtual void remove_joy_mapping(String p_guid);
	virtual bool is_joy_known(int p_device);
	virtual String get_joy_guid(int p_device) const;

	virtual bool should_ignore_device(int p_vendor_id, int p_product_id) const;

	virtual void start_joy_vibration(int p_device, float p_weak_magnitude, float p_strong_magnitude, float p_duration = 0);
	virtual void stop_joy_vibration(int p_device);
	virtual void vibrate_handheld(int p_duration_ms = 500);

	void set_joy_axis(int p_device, int p_axis, float p_value);

	void parse_mapping(String p_mapping);
	void joy_button(int p_device, int p_button, bool p_pressed);
	void joy_axis(int p_device, int p_axis, float p_value);
	void joy_hat(int p_device, int p_val);

	virtual Point2 get_mouse_position() const;
	virtual Point2 get_last_mouse_speed();
	virtual int get_mouse_button_mask() const;

	void set_mouse_position(const Point2 &p_posf);

	virtual void warp_mouse_position(const Vector2 &p_to);
	virtual Point2i warp_mouse_motion(const Ref<InputEventMouseMotion> &p_motion, const Rect2 &p_rect);

	virtual Vector3 get_gravity() const;
	virtual Vector3 get_accelerometer() const;
	virtual Vector3 get_magnetometer() const;
	virtual Vector3 get_gyroscope() const;

	virtual void set_gravity(const Vector3 &p_gravity);
	virtual void set_accelerometer(const Vector3 &p_accel);
	virtual void set_magnetometer(const Vector3 &p_magnetometer);
	virtual void set_gyroscope(const Vector3 &p_gyroscope);

	virtual void action_press(const StringName &p_action, float p_strength = 1.f);
	virtual void action_release(const StringName &p_action);

	void set_emulate_touch_from_mouse(bool p_emulate);
	virtual bool is_emulating_touch_from_mouse() const;
	void ensure_touch_mouse_raised();

	void set_emulate_mouse_from_touch(bool p_emulate);
	virtual bool is_emulating_mouse_from_touch() const;

	virtual CursorShape get_default_cursor_shape() const;
	virtual void set_default_cursor_shape(CursorShape p_shape);
	virtual CursorShape get_current_cursor_shape() const;
	virtual void set_custom_mouse_cursor(const Ref<Reference> &p_cursor, CursorShape p_shape = CURSOR_ARROW, const Vector2 &p_hotspot = Vector2());

	virtual String get_joy_button_string(int p_button);
	virtual String get_joy_axis_string(int p_axis);
	virtual int get_joy_axis_index_from_string(String p_axis);
	virtual int get_joy_button_index_from_string(String p_button);

	int get_unused_joy_id();

	bool is_joy_mapped(int p_device);
	String get_joy_guid_remapped(int p_device) const;
	void set_fallback_mapping(String p_guid);

	virtual void parse_input_event(const Ref<InputEvent> &p_event);

	virtual void flush_buffered_events();
	virtual bool is_using_input_buffering();
	virtual void set_use_input_buffering(bool p_enable);
	virtual bool is_using_accumulated_input();
	virtual void set_use_accumulated_input(bool p_enable);

	virtual void release_pressed_events();

	void get_argument_options(const StringName &p_function, int p_idx, List<String> *r_options, const String &quote_style) const;

	void set_main_loop(Application *p_main_loop);
	void iteration(real_t p_step);

	Input();

	//Called by AppWindow
	void _setup_window_callbacks();

protected:
	static void GLFWkeyfunCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void GLFWcharfunCallback(GLFWwindow *window, unsigned int codepoint);
	static void GLFWcharmodsfunCallback(GLFWwindow *window, unsigned int codepoint, int mods);
	static void GLFWmousebuttonfunCallback(GLFWwindow *window, int button, int action, int mods);
	static void GLFWcursorposfunCallback(GLFWwindow *window, double xpos, double ypos);
	static void GLFWcursorenterfunCallback(GLFWwindow *window, int entered);
	static void GLFWscrollfunCallback(GLFWwindow *window, double xoffset, double yoffset);
	static void GLFWdropfunCallback(GLFWwindow *window, int path_count, const char *paths[]);
	static void GLFWjoystickfunCallback(int jid, int event);

protected:
	enum JoyType {
		TYPE_BUTTON,
		TYPE_AXIS,
		TYPE_HAT,
		TYPE_MAX,
	};

	enum JoyAxisRange {
		NEGATIVE_HALF_AXIS = -1,
		FULL_AXIS = 0,
		POSITIVE_HALF_AXIS = 1
	};

	struct JoyEvent {
		int type;
		int index;
		float value;
	};

	struct JoyBinding {
		JoyType inputType;
		union {
			int button;

			struct {
				int axis;
				JoyAxisRange range;
				bool invert;
			} axis;

			struct {
				int hat;
				HatMask hat_mask;
			} hat;

		} input;

		JoyType outputType;
		union {
			JoystickList button;

			struct {
				JoystickList axis;
				JoyAxisRange range;
			} axis;

		} output;
	};

	struct JoyDeviceMapping {
		String uid;
		String name;
		Vector<JoyBinding> bindings;
	};

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

	struct Joypad {
		StringName name;
		StringName uid;
		bool connected;
		bool last_buttons[JOY_BUTTON_MAX + 12]; //apparently SDL specifies 35 possible buttons on android
		float last_axis[JOY_AXIS_MAX];
		int last_hat;
		int mapping;
		int hat_current;

		Joypad() {
			for (int i = 0; i < JOY_AXIS_MAX; i++) {
				last_axis[i] = 0.0f;
			}
			for (int i = 0; i < JOY_BUTTON_MAX + 12; i++) {
				last_buttons[i] = false;
			}
			connected = false;
			last_hat = HAT_MASK_CENTER;
			mapping = -1;
			hat_current = 0;
		}
	};

	struct VibrationInfo {
		float weak_magnitude;
		float strong_magnitude;
		float duration; // Duration in seconds
		uint64_t timestamp;
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

	JoyEvent _get_mapped_button_event(const JoyDeviceMapping &mapping, int p_button);
	JoyEvent _get_mapped_axis_event(const JoyDeviceMapping &mapping, int p_axis, float p_value);
	void _get_mapped_hat_events(const JoyDeviceMapping &mapping, int p_hat, JoyEvent r_events[HAT_MAX]);
	JoystickList _get_output_button(String output);
	JoystickList _get_output_axis(String output);
	void _button_event(int p_device, int p_index, bool p_pressed);
	void _axis_event(int p_device, int p_axis, float p_value);

	void _parse_input_event_impl(const Ref<InputEvent> &p_event, bool p_is_emulated);

	static String _hex_str(uint8_t p_byte);

	List<Ref<InputEvent>> buffered_events;
	bool use_input_buffering;
	bool use_accumulated_input;

	int mouse_button_mask;

	RBSet<int> physical_keys_pressed;
	RBSet<int> keys_pressed;
	RBSet<int> joy_buttons_pressed;
	RBMap<int, float> _joy_axis;
	//Map<StringName,int> custom_action_press;
	Vector3 gravity;
	Vector3 accelerometer;
	Vector3 magnetometer;
	Vector3 gyroscope;
	Vector2 mouse_pos;
	Application *main_loop;
	bool legacy_just_pressed_behavior;

	RBMap<StringName, Action> action_state;

	bool emulate_touch_from_mouse;
	bool emulate_mouse_from_touch;

	int mouse_from_touch_index;

	SpeedTrack mouse_speed_track;
	RBMap<int, SpeedTrack> touch_speed_track;
	RBMap<int, Joypad> joy_names;
	int fallback_mapping;

	CursorShape default_shape;

	Vector<JoyDeviceMapping> map_db;

	RBSet<uint32_t> ignored_device_ids;

	RBMap<int, VibrationInfo> joy_vibration;

	static Input *singleton;
};

#endif // INPUT_H
