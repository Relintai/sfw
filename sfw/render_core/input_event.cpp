/*************************************************************************/
/*  input_event.cpp                                                      */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "input_event.h"

#include "render_core/input_map.h"
#include "render_core/keyboard.h"
#include "render_core/shortcut.h"

const int InputEvent::DEVICE_ID_TOUCH_MOUSE = -1;
const int InputEvent::DEVICE_ID_INTERNAL = -2;

void InputEvent::set_device(int p_device) {
	device = p_device;
}

int InputEvent::get_device() const {
	return device;
}

bool InputEvent::is_action(const StringName &p_action, bool p_exact_match) const {
	return InputMap::get_singleton()->event_is_action(Ref<InputEvent>((InputEvent *)this), p_action, p_exact_match);
}

bool InputEvent::is_action_pressed(const StringName &p_action, bool p_allow_echo, bool p_exact_match) const {
	bool pressed = false;
	bool valid = InputMap::get_singleton()->event_get_action_status(Ref<InputEvent>((InputEvent *)this), p_action, p_exact_match, &pressed, nullptr, nullptr);
	return valid && pressed && (p_allow_echo || !is_echo());
}

bool InputEvent::is_action_released(const StringName &p_action, bool p_exact_match) const {
	bool pressed = false;
	bool valid = InputMap::get_singleton()->event_get_action_status(Ref<InputEvent>((InputEvent *)this), p_action, p_exact_match, &pressed, nullptr, nullptr);
	return valid && !pressed;
}

float InputEvent::get_action_strength(const StringName &p_action, bool p_exact_match) const {
	float strength = 0.0f;
	bool valid = InputMap::get_singleton()->event_get_action_status(Ref<InputEvent>((InputEvent *)this), p_action, p_exact_match, nullptr, &strength, nullptr);
	return valid ? strength : 0.0f;
}

float InputEvent::get_action_raw_strength(const StringName &p_action, bool p_exact_match) const {
	float raw_strength = 0.0f;
	bool valid = InputMap::get_singleton()->event_get_action_status(Ref<InputEvent>((InputEvent *)this), p_action, p_exact_match, nullptr, nullptr, &raw_strength);
	return valid ? raw_strength : 0.0f;
}

bool InputEvent::is_canceled() const {
	return canceled;
}

bool InputEvent::is_pressed() const {
	return pressed && !canceled;
}

bool InputEvent::is_released() const {
	return !pressed && !canceled;
}

bool InputEvent::is_echo() const {
	return false;
}

Ref<InputEvent> InputEvent::xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs) const {
	return Ref<InputEvent>((InputEvent *)this);
}

String InputEvent::as_text() const {
	return String();
}

bool InputEvent::action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const {
	return false;
}

bool InputEvent::shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match) const {
	return false;
}

bool InputEvent::is_action_type() const {
	return false;
}

InputEvent::InputEvent() {
	device = 0;
	canceled = false;
	pressed = false;
}

//////////////////

void InputEventWithModifiers::set_shift(bool p_enabled) {
	shift = p_enabled;
}

bool InputEventWithModifiers::get_shift() const {
	return shift;
}

void InputEventWithModifiers::set_alt(bool p_enabled) {
	alt = p_enabled;
}
bool InputEventWithModifiers::get_alt() const {
	return alt;
}

void InputEventWithModifiers::set_control(bool p_enabled) {
	control = p_enabled;
}
bool InputEventWithModifiers::get_control() const {
	return control;
}

void InputEventWithModifiers::set_metakey(bool p_enabled) {
	meta = p_enabled;
}
bool InputEventWithModifiers::get_metakey() const {
	return meta;
}

void InputEventWithModifiers::set_command(bool p_enabled) {
	command = p_enabled;
}
bool InputEventWithModifiers::get_command() const {
	return command;
}

void InputEventWithModifiers::set_modifiers_from_event(const InputEventWithModifiers *event) {
	set_alt(event->get_alt());
	set_shift(event->get_shift());
	set_control(event->get_control());
	set_metakey(event->get_metakey());
}

uint32_t InputEventWithModifiers::get_modifiers_mask() const {
	uint32_t mask = 0;
	if (get_control()) {
		mask |= KEY_MASK_CTRL;
	}
	if (get_shift()) {
		mask |= KEY_MASK_SHIFT;
	}
	if (get_alt()) {
		mask |= KEY_MASK_ALT;
	}
	if (get_metakey()) {
		mask |= KEY_MASK_META;
	}
	return mask;
}

InputEventWithModifiers::InputEventWithModifiers() {
	alt = false;
	shift = false;
	control = false;
	meta = false;
}

//////////////////////////////////

void InputEventKey::set_pressed(bool p_pressed) {
	pressed = p_pressed;
}

void InputEventKey::set_scancode(uint32_t p_scancode) {
	scancode = p_scancode;
}
uint32_t InputEventKey::get_scancode() const {
	return scancode;
}

void InputEventKey::set_physical_scancode(uint32_t p_scancode) {
	physical_scancode = p_scancode;
}
uint32_t InputEventKey::get_physical_scancode() const {
	return physical_scancode;
}

void InputEventKey::set_unicode(uint32_t p_unicode) {
	unicode = p_unicode;
}
uint32_t InputEventKey::get_unicode() const {
	return unicode;
}

void InputEventKey::set_echo(bool p_enable) {
	echo = p_enable;
}
bool InputEventKey::is_echo() const {
	return echo;
}

void InputEventKey::set_action_match_force_exact(bool p_enable) {
	action_match_force_exact = p_enable;
}
bool InputEventKey::is_action_match_force_exact() const {
	return action_match_force_exact;
}

uint32_t InputEventKey::get_scancode_with_modifiers() const {
	return scancode | get_modifiers_mask();
}

uint32_t InputEventKey::get_physical_scancode_with_modifiers() const {
	return physical_scancode | get_modifiers_mask();
}

String InputEventKey::as_text() const {
	String kc;

	if (scancode == 0) {
		kc = keycode_get_string(physical_scancode) + " (" + RTR("Physical") + ")";
	} else {
		kc = keycode_get_string(scancode);
	}

	if (kc == String()) {
		return kc;
	}

	if (get_metakey()) {
		kc = find_keycode_name(KEY_META) + ("+" + kc);
	}
	if (get_alt()) {
		kc = find_keycode_name(KEY_ALT) + ("+" + kc);
	}
	if (get_shift()) {
		kc = find_keycode_name(KEY_SHIFT) + ("+" + kc);
	}
	if (get_control()) {
		kc = find_keycode_name(KEY_CONTROL) + ("+" + kc);
	}
	return kc;
}

bool InputEventKey::action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const {
	Ref<InputEventKey> key = p_event;
	if (key.is_null()) {
		return false;
	}

	if (action_match_force_exact) {
		uint32_t code = get_scancode_with_modifiers();
		uint32_t event_code = key->get_scancode_with_modifiers();

		bool match = (code == event_code);
		if (match) {
			if (p_pressed != NULL) {
				*p_pressed = key->is_pressed();
			}
			if (p_strength != NULL) {
				*p_strength = (p_pressed != NULL && *p_pressed) ? 1.0f : 0.0f;
			}
		}
		return match;
	}

	bool match;
	if (scancode != 0) {
		match = scancode == key->scancode;
	} else {
		match = physical_scancode == key->physical_scancode;
	}
	uint32_t action_mask = get_modifiers_mask();
	uint32_t key_mask = key->get_modifiers_mask();
	if (key->is_pressed()) {
		match &= (action_mask & key_mask) == action_mask;
	}
	if (p_exact_match) {
		match &= action_mask == key_mask;
	}
	if (match) {
		bool pressed = key->is_pressed();
		if (p_pressed != nullptr) {
			*p_pressed = pressed;
		}
		float strength = pressed ? 1.0f : 0.0f;
		if (p_strength != nullptr) {
			*p_strength = strength;
		}
		if (p_raw_strength != nullptr) {
			*p_raw_strength = strength;
		}
	}
	return match;
}

bool InputEventKey::shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match) const {
	Ref<InputEventKey> key = p_event;
	if (key.is_null()) {
		return false;
	}

	if (scancode == 0) {
		return physical_scancode == key->physical_scancode &&
				(!p_exact_match || get_modifiers_mask() == key->get_modifiers_mask());
	} else {
		return scancode == key->scancode &&
				(!p_exact_match || get_modifiers_mask() == key->get_modifiers_mask());
	}
}

InputEventKey::InputEventKey() {
	scancode = 0;
	physical_scancode = 0;
	unicode = 0; ///unicode
	echo = false;
	action_match_force_exact = false;
}

////////////////////////////////////////

void InputEventMouse::set_button_mask(int p_mask) {
	button_mask = p_mask;
}
int InputEventMouse::get_button_mask() const {
	return button_mask;
}

void InputEventMouse::set_position(const Vector2 &p_pos) {
	pos = p_pos;
}
Vector2 InputEventMouse::get_position() const {
	return pos;
}

void InputEventMouse::set_global_position(const Vector2 &p_global_pos) {
	global_pos = p_global_pos;
}
Vector2 InputEventMouse::get_global_position() const {
	return global_pos;
}

InputEventMouse::InputEventMouse() {
	button_mask = 0;
}

///////////////////////////////////////

void InputEventMouseButton::set_factor(float p_factor) {
	factor = p_factor;
}

float InputEventMouseButton::get_factor() const {
	return factor;
}

void InputEventMouseButton::set_button_index(int p_index) {
	button_index = p_index;
}
int InputEventMouseButton::get_button_index() const {
	return button_index;
}

void InputEventMouseButton::set_pressed(bool p_pressed) {
	pressed = p_pressed;
}
void InputEventMouseButton::set_canceled(bool p_canceled) {
	canceled = p_canceled;
}

void InputEventMouseButton::set_doubleclick(bool p_doubleclick) {
	doubleclick = p_doubleclick;
}
bool InputEventMouseButton::is_doubleclick() const {
	return doubleclick;
}

Ref<InputEvent> InputEventMouseButton::xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs) const {
	Vector2 g = get_global_position();
	Vector2 l = p_xform.xform(get_position() + p_local_ofs);

	Ref<InputEventMouseButton> mb;
	mb.instance();

	mb->set_device(get_device());

	mb->set_modifiers_from_event(this);

	mb->set_position(l);
	mb->set_global_position(g);

	mb->set_button_mask(get_button_mask());
	mb->set_pressed(pressed);
	mb->set_canceled(canceled);
	mb->set_doubleclick(doubleclick);
	mb->set_factor(factor);
	mb->set_button_index(button_index);

	return mb;
}

bool InputEventMouseButton::action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const {
	Ref<InputEventMouseButton> mb = p_event;
	if (mb.is_null()) {
		return false;
	}

	bool match = mb->button_index == button_index;
	uint32_t action_mask = get_modifiers_mask();
	uint32_t button_mask = mb->get_modifiers_mask();
	if (mb->is_pressed()) {
		match &= (action_mask & button_mask) == action_mask;
	}
	if (p_exact_match) {
		match &= action_mask == button_mask;
	}
	if (match) {
		bool pressed = mb->is_pressed();
		if (p_pressed != nullptr) {
			*p_pressed = pressed;
		}
		float strength = pressed ? 1.0f : 0.0f;
		if (p_strength != nullptr) {
			*p_strength = strength;
		}
		if (p_raw_strength != nullptr) {
			*p_raw_strength = strength;
		}
	}

	return match;
}

bool InputEventMouseButton::shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match) const {
	Ref<InputEventMouseButton> mb = p_event;
	if (mb.is_null()) {
		return false;
	}

	return button_index == mb->button_index &&
			(!p_exact_match || get_modifiers_mask() == mb->get_modifiers_mask());
}

String InputEventMouseButton::as_text() const {
	String button_index_string = "";
	switch (get_button_index()) {
		case BUTTON_LEFT:
			button_index_string = "BUTTON_LEFT";
			break;
		case BUTTON_RIGHT:
			button_index_string = "BUTTON_RIGHT";
			break;
		case BUTTON_MIDDLE:
			button_index_string = "BUTTON_MIDDLE";
			break;
		case BUTTON_WHEEL_UP:
			button_index_string = "BUTTON_WHEEL_UP";
			break;
		case BUTTON_WHEEL_DOWN:
			button_index_string = "BUTTON_WHEEL_DOWN";
			break;
		case BUTTON_WHEEL_LEFT:
			button_index_string = "BUTTON_WHEEL_LEFT";
			break;
		case BUTTON_WHEEL_RIGHT:
			button_index_string = "BUTTON_WHEEL_RIGHT";
			break;
		case BUTTON_XBUTTON1:
			button_index_string = "BUTTON_XBUTTON1";
			break;
		case BUTTON_XBUTTON2:
			button_index_string = "BUTTON_XBUTTON2";
			break;
		default:
			button_index_string = itos(get_button_index());
			break;
	}
	return "InputEventMouseButton : button_index=" + button_index_string + ", pressed=" + (pressed ? "true" : "false") + ", canceled=" + (canceled ? "true" : "false") + ", position=(" + String(get_position()) + "), button_mask=" + itos(get_button_mask()) + ", doubleclick=" + (doubleclick ? "true" : "false");
}

InputEventMouseButton::InputEventMouseButton() {
	factor = 1;
	button_index = 0;
	doubleclick = false;
}

////////////////////////////////////////////

void InputEventMouseMotion::set_tilt(const Vector2 &p_tilt) {
	tilt = p_tilt;
}

Vector2 InputEventMouseMotion::get_tilt() const {
	return tilt;
}

void InputEventMouseMotion::set_pressure(float p_pressure) {
	pressure = p_pressure;
}

float InputEventMouseMotion::get_pressure() const {
	return pressure;
}

void InputEventMouseMotion::set_pen_inverted(bool p_inverted) {
	pen_inverted = p_inverted;
}

bool InputEventMouseMotion::get_pen_inverted() const {
	return pen_inverted;
}

void InputEventMouseMotion::set_relative(const Vector2 &p_relative) {
	relative = p_relative;
}

Vector2 InputEventMouseMotion::get_relative() const {
	return relative;
}

void InputEventMouseMotion::set_speed(const Vector2 &p_speed) {
	speed = p_speed;
}

Vector2 InputEventMouseMotion::get_speed() const {
	return speed;
}

Ref<InputEvent> InputEventMouseMotion::xformed_by(const Transform2D &p_xform, const Vector2 &p_local_ofs) const {
	Vector2 g = get_global_position();
	Vector2 l = p_xform.xform(get_position() + p_local_ofs);
	Vector2 r = p_xform.basis_xform(get_relative());
	Vector2 s = p_xform.basis_xform(get_speed());

	Ref<InputEventMouseMotion> mm;
	mm.instance();

	mm->set_device(get_device());

	mm->set_modifiers_from_event(this);

	mm->set_position(l);
	mm->set_pressure(get_pressure());
	mm->set_pen_inverted(get_pen_inverted());
	mm->set_tilt(get_tilt());
	mm->set_global_position(g);

	mm->set_button_mask(get_button_mask());
	mm->set_relative(r);
	mm->set_speed(s);

	return mm;
}

String InputEventMouseMotion::as_text() const {
	String button_mask_string = "";
	switch (get_button_mask()) {
		case BUTTON_MASK_LEFT:
			button_mask_string = "BUTTON_MASK_LEFT";
			break;
		case BUTTON_MASK_MIDDLE:
			button_mask_string = "BUTTON_MASK_MIDDLE";
			break;
		case BUTTON_MASK_RIGHT:
			button_mask_string = "BUTTON_MASK_RIGHT";
			break;
		case BUTTON_MASK_XBUTTON1:
			button_mask_string = "BUTTON_MASK_XBUTTON1";
			break;
		case BUTTON_MASK_XBUTTON2:
			button_mask_string = "BUTTON_MASK_XBUTTON2";
			break;
		default:
			button_mask_string = itos(get_button_mask());
			break;
	}
	return "InputEventMouseMotion : button_mask=" + button_mask_string + ", position=(" + String(get_position()) + "), relative=(" + String(get_relative()) + "), speed=(" + String(get_speed()) + "), pressure=(" + rtos(get_pressure()) + "), tilt=(" + String(get_tilt()) + "), pen_inverted=(" + rtos(get_pen_inverted()) + ")";
}

bool InputEventMouseMotion::accumulate(const Ref<InputEvent> &p_event) {
	Ref<InputEventMouseMotion> motion = p_event;
	if (motion.is_null()) {
		return false;
	}

	if (is_canceled() != motion->is_canceled()) {
		return false;
	}

	if (is_pressed() != motion->is_pressed()) {
		return false;
	}

	if (get_button_mask() != motion->get_button_mask()) {
		return false;
	}

	if (get_shift() != motion->get_shift()) {
		return false;
	}

	if (get_control() != motion->get_control()) {
		return false;
	}

	if (get_alt() != motion->get_alt()) {
		return false;
	}

	if (get_metakey() != motion->get_metakey()) {
		return false;
	}

	set_position(motion->get_position());
	set_global_position(motion->get_global_position());
	set_speed(motion->get_speed());
	relative += motion->get_relative();

	return true;
}

InputEventMouseMotion::InputEventMouseMotion() {
	pressure = 0;
	pen_inverted = false;
}

/////////////////////////////

void InputEventAction::set_action(const StringName &p_action) {
	action = p_action;
}
StringName InputEventAction::get_action() const {
	return action;
}

void InputEventAction::set_pressed(bool p_pressed) {
	pressed = p_pressed;
}

void InputEventAction::set_strength(float p_strength) {
	strength = CLAMP(p_strength, 0.0f, 1.0f);
}

float InputEventAction::get_strength() const {
	return strength;
}

bool InputEventAction::shortcut_match(const Ref<InputEvent> &p_event, bool p_exact_match) const {
	if (p_event.is_null()) {
		return false;
	}

	return p_event->is_action(action, p_exact_match);
}

bool InputEventAction::is_action(const StringName &p_action) const {
	return action == p_action;
}

bool InputEventAction::action_match(const Ref<InputEvent> &p_event, bool p_exact_match, bool *p_pressed, float *p_strength, float *p_raw_strength, float p_deadzone) const {
	Ref<InputEventAction> act = p_event;
	if (act.is_null()) {
		return false;
	}

	bool match = action == act->action;
	if (match) {
		bool pressed = act->is_pressed();
		if (p_pressed != nullptr) {
			*p_pressed = pressed;
		}
		float strength = pressed ? 1.0f : 0.0f;
		if (p_strength != nullptr) {
			*p_strength = strength;
		}
		if (p_raw_strength != nullptr) {
			*p_raw_strength = strength;
		}
	}
	return match;
}

String InputEventAction::as_text() const {
	return "InputEventAction : action=" + action + ", pressed=(" + (is_pressed() ? "true" : "false");
}

InputEventAction::InputEventAction() {
	strength = 1.0f;
}
/////////////////////////////

void InputEventShortCut::set_shortcut(Ref<ShortCut> p_shortcut) {
	shortcut = p_shortcut;
	emit_changed();
}

Ref<ShortCut> InputEventShortCut::get_shortcut() {
	return shortcut;
}

String InputEventShortCut::as_text() const {
	ERR_FAIL_COND_V(shortcut.is_null(), "None");

	return vformat(RTR("Input Event with ShortCut=%s"), shortcut->get_as_text());
}

String InputEventShortCut::to_string() {
	ERR_FAIL_COND_V(shortcut.is_null(), "None");

	return vformat("InputEventShortCut: shortcut=%s", shortcut->get_as_text());
}

InputEventShortCut::InputEventShortCut() {
}

InputEventShortCut::~InputEventShortCut() {
}