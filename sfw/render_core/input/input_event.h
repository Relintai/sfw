#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

/*************************************************************************/
/*  input_event.h                                                        */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "core/transform_2d.h"
#include "core/typedefs.h"
#include "core/ustring.h"
#include "object/resource.h"

/**
 * Input Event classes. These are used in the main loop.
 * The events are pretty obvious.
 */

class ShortCut;

enum ButtonList {
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
	BUTTON_MIDDLE = 3,
	BUTTON_WHEEL_UP = 4,
	BUTTON_WHEEL_DOWN = 5,
	BUTTON_WHEEL_LEFT = 6,
	BUTTON_WHEEL_RIGHT = 7,
	BUTTON_XBUTTON1 = 8,
	BUTTON_XBUTTON2 = 9,
	BUTTON_MASK_LEFT = (1 << (BUTTON_LEFT - 1)),
	BUTTON_MASK_RIGHT = (1 << (BUTTON_RIGHT - 1)),
	BUTTON_MASK_MIDDLE = (1 << (BUTTON_MIDDLE - 1)),
	BUTTON_MASK_XBUTTON1 = (1 << (BUTTON_XBUTTON1 - 1)),
	BUTTON_MASK_XBUTTON2 = (1 << (BUTTON_XBUTTON2 - 1))
};

/**
 * Input Modifier Status
 * for keyboard/mouse events.
 */

class InputEvent : public Resource {
	SFW_OBJECT(InputEvent, Resource);

	int device;

protected:
	bool canceled;
	bool pressed;

public:
	static const int DEVICE_ID_TOUCH_MOUSE;
	static const int DEVICE_ID_INTERNAL;

	void set_device(int p_device);
	int get_device() const;

	bool is_action(const StringName &p_action, bool p_exact_match = false) const;
	bool is_action_pressed(const StringName &p_action, bool p_allow_echo = false, bool p_exact_match = false) const;
	bool is_action_released(const StringName &p_action, bool p_exact_match = false) const;
	float get_action_strength(const StringName &p_action, bool p_exact_match = false) const;
	float get_action_raw_strength(const StringName &p_action, bool p_exact_match = false) const;

	bool is_canceled() const;
	bool is_pressed() const;
	bool is_released() const;
	virtual bool is_echo() const;
	// ...-.

	virtual String as_text() const;

	virtual Ref<InputEvent> xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs = Vector2()) const;

	virtual bool action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const;
	virtual bool shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match = true) const;
	virtual bool is_action_type() const;

	virtual bool accumulate(const Ref<InputEvent> &p_event) { return false; }
	InputEvent();
};

class InputEventWithModifiers : public InputEvent {
	SFW_OBJECT(InputEventWithModifiers, InputEvent);

	bool shift;
	bool alt;
#ifdef APPLE_STYLE_KEYS
	union {
		bool command;
		bool meta; //< windows/mac key
	};

	bool control;
#else
	union {
		bool command; //< windows/mac key
		bool control;
	};
	bool meta; //< windows/mac key

#endif

public:
	void set_shift(bool p_enabled);
	bool get_shift() const;

	void set_alt(bool p_enabled);
	bool get_alt() const;

	void set_control(bool p_enabled);
	bool get_control() const;

	void set_metakey(bool p_enabled);
	bool get_metakey() const;

	void set_command(bool p_enabled);
	bool get_command() const;

	void set_modifiers_from_event(const InputEventWithModifiers *event);

	uint32_t get_modifiers_mask() const;

	InputEventWithModifiers();
};

class InputEventKey : public InputEventWithModifiers {
	SFW_OBJECT(InputEventKey, InputEventWithModifiers);

	uint32_t scancode; ///< check keyboard.h , KeyCode enum, without modifier masks
	uint32_t physical_scancode;
	uint32_t unicode; ///unicode

	bool echo; /// true if this is an echo key

	bool action_match_force_exact;

public:
	void set_pressed(bool p_pressed);

	void set_scancode(uint32_t p_scancode);
	uint32_t get_scancode() const;

	void set_physical_scancode(uint32_t p_scancode);
	uint32_t get_physical_scancode() const;

	void set_unicode(uint32_t p_unicode);
	uint32_t get_unicode() const;

	void set_echo(bool p_enable);
	virtual bool is_echo() const;

	void set_action_match_force_exact(bool p_enable);
	bool is_action_match_force_exact() const;

	uint32_t get_scancode_with_modifiers() const;
	uint32_t get_physical_scancode_with_modifiers() const;

	virtual bool action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const;
	virtual bool shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match = true) const;

	virtual bool is_action_type() const { return true; }

	virtual String as_text() const;

	InputEventKey();
};

class InputEventMouse : public InputEventWithModifiers {
	SFW_OBJECT(InputEventMouse, InputEventWithModifiers);

	int button_mask;

	Vector2 pos;
	Vector2 global_pos;

public:
	void set_button_mask(int p_mask);
	int get_button_mask() const;

	void set_position(const Vector2 &p_pos);
	Vector2 get_position() const;

	void set_global_position(const Vector2 &p_global_pos);
	Vector2 get_global_position() const;

	InputEventMouse();
};

class InputEventMouseButton : public InputEventMouse {
	SFW_OBJECT(InputEventMouseButton, InputEventMouse);

	float factor;
	int button_index;
	bool doubleclick; //last even less than doubleclick time

public:
	void set_factor(float p_factor);
	float get_factor() const;

	void set_button_index(int p_index);
	int get_button_index() const;

	void set_pressed(bool p_pressed);
	void set_canceled(bool p_canceled);

	void set_doubleclick(bool p_doubleclick);
	bool is_doubleclick() const;

	virtual Ref<InputEvent> xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs = Vector2()) const;
	virtual bool action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const;
	virtual bool shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match = true) const;

	virtual bool is_action_type() const { return true; }
	virtual String as_text() const;

	InputEventMouseButton();
};

class InputEventMouseMotion : public InputEventMouse {
	SFW_OBJECT(InputEventMouseMotion, InputEventMouse);

	Vector2 tilt;
	float pressure;
	Vector2 relative;
	Vector2 speed;
	bool pen_inverted;

public:
	void set_tilt(const Vector2 &p_tilt);
	Vector2 get_tilt() const;

	void set_pressure(float p_pressure);
	float get_pressure() const;

	void set_pen_inverted(bool p_inverted);
	bool get_pen_inverted() const;

	void set_relative(const Vector2 &p_relative);
	Vector2 get_relative() const;

	void set_speed(const Vector2 &p_speed);
	Vector2 get_speed() const;

	virtual Ref<InputEvent> xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs = Vector2()) const;
	virtual String as_text() const;

	virtual bool accumulate(const Ref<InputEvent> &p_event);

	InputEventMouseMotion();
};

class InputEventAction : public InputEvent {
	SFW_OBJECT(InputEventAction, InputEvent);

	StringName action;
	float strength;

public:
	void set_action(const StringName &p_action);
	StringName get_action() const;

	void set_pressed(bool p_pressed);

	void set_strength(float p_strength);
	float get_strength() const;

	virtual bool is_action(const StringName &p_action) const;

	virtual bool action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const;
	virtual bool shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match = true) const;

	virtual bool is_action_type() const { return true; }
	virtual String as_text() const;

	InputEventAction();
};

class InputEventShortCut : public InputEvent {
	SFW_OBJECT(InputEventShortCut, InputEvent);

	Ref<ShortCut> shortcut;

public:
	void set_shortcut(Ref<ShortCut> p_shortcut);
	Ref<ShortCut> get_shortcut();

	virtual String as_text() const;
	virtual String to_string();

	InputEventShortCut();
	~InputEventShortCut();
};

#endif
