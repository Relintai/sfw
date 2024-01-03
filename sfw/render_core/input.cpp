/*************************************************************************/
/*  input.cpp                                                            */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "input.h"

#include "core/logger.h"
#include "core/stime.h"
#include "render_core/application.h"
#include "render_core/input_map.h"
#include "render_core/keyboard.h"
#include "render_core/texture.h"
#include "render_core/window.h"

#include "render_core/3rd_glfw3.h"

Input *Input::get_singleton() {
	return singleton;
}

void Input::set_mouse_mode(MouseMode p_mode) {
	AppWindow::get_singleton()->set_mouse_mode((AppWindow::MouseMode)p_mode);
}

Input::MouseMode Input::get_mouse_mode() const {
	return (MouseMode)AppWindow::get_singleton()->get_mouse_mode();
}

bool Input::is_key_pressed(int p_scancode) const {
	_THREAD_SAFE_METHOD_
	return keys_pressed.has(p_scancode);
}

bool Input::is_physical_key_pressed(int p_scancode) const {
	_THREAD_SAFE_METHOD_
	return physical_keys_pressed.has(p_scancode);
}

bool Input::is_mouse_button_pressed(int p_button) const {
	_THREAD_SAFE_METHOD_
	return (mouse_button_mask & (1 << (p_button - 1))) != 0;
}

bool Input::is_action_pressed(const StringName &p_action, bool p_exact) const {
	ERR_FAIL_COND_V_MSG(!InputMap::get_singleton()->has_action(p_action), false, InputMap::get_singleton()->suggest_actions(p_action));
	return action_state.has(p_action) && action_state[p_action].pressed && (p_exact ? action_state[p_action].exact : true);
}

bool Input::is_action_just_pressed(const StringName &p_action, bool p_exact) const {
	ERR_FAIL_COND_V_MSG(!InputMap::get_singleton()->has_action(p_action), false, InputMap::get_singleton()->suggest_actions(p_action));
	const RBMap<StringName, Action>::Element *E = action_state.find(p_action);
	if (!E) {
		return false;
	}

	if (p_exact && E->get().exact == false) {
		return false;
	}

	// Backward compatibility for legacy behavior, only return true if currently pressed.
	bool pressed_requirement = legacy_just_pressed_behavior ? E->get().pressed : true;

	return pressed_requirement && E->get().pressed_idle_frame == Application::get_singleton()->get_idle_frames();
}

bool Input::is_action_just_released(const StringName &p_action, bool p_exact) const {
	ERR_FAIL_COND_V_MSG(!InputMap::get_singleton()->has_action(p_action), false, InputMap::get_singleton()->suggest_actions(p_action));
	const RBMap<StringName, Action>::Element *E = action_state.find(p_action);
	if (!E) {
		return false;
	}

	if (p_exact && E->get().exact == false) {
		return false;
	}

	// Backward compatibility for legacy behavior, only return true if currently released.
	bool released_requirement = legacy_just_pressed_behavior ? !E->get().pressed : true;

	return released_requirement && E->get().released_idle_frame == Application::get_singleton()->get_idle_frames();
}

float Input::get_action_strength(const StringName &p_action, bool p_exact) const {
	ERR_FAIL_COND_V_MSG(!InputMap::get_singleton()->has_action(p_action), 0.0, InputMap::get_singleton()->suggest_actions(p_action));
	const RBMap<StringName, Action>::Element *E = action_state.find(p_action);
	if (!E) {
		return 0.0f;
	}

	if (p_exact && E->get().exact == false) {
		return 0.0f;
	}

	return E->get().strength;
}

float Input::get_action_raw_strength(const StringName &p_action, bool p_exact) const {
	ERR_FAIL_COND_V_MSG(!InputMap::get_singleton()->has_action(p_action), 0.0, InputMap::get_singleton()->suggest_actions(p_action));
	const RBMap<StringName, Action>::Element *E = action_state.find(p_action);
	if (!E) {
		return 0.0f;
	}

	if (p_exact && E->get().exact == false) {
		return 0.0f;
	}

	return E->get().raw_strength;
}

float Input::get_axis(const StringName &p_negative_action, const StringName &p_positive_action) const {
	return get_action_strength(p_positive_action) - get_action_strength(p_negative_action);
}

Vector2 Input::get_vector(const StringName &p_negative_x, const StringName &p_positive_x, const StringName &p_negative_y, const StringName &p_positive_y, float p_deadzone) const {
	Vector2 vector = Vector2(
			get_action_raw_strength(p_positive_x) - get_action_raw_strength(p_negative_x),
			get_action_raw_strength(p_positive_y) - get_action_raw_strength(p_negative_y));

	if (p_deadzone < 0.0f) {
		// If the deadzone isn't specified, get it from the average of the actions.
		p_deadzone = 0.25 *
				(InputMap::get_singleton()->action_get_deadzone(p_positive_x) +
						InputMap::get_singleton()->action_get_deadzone(p_negative_x) +
						InputMap::get_singleton()->action_get_deadzone(p_positive_y) +
						InputMap::get_singleton()->action_get_deadzone(p_negative_y));
	}

	// Circular length limiting and deadzone.
	float length = vector.length();
	if (length <= p_deadzone) {
		return Vector2();
	} else if (length > 1.0f) {
		return vector / length;
	} else {
		// Inverse lerp length to map (p_deadzone, 1) to (0, 1).
		return vector * (Math::inverse_lerp(p_deadzone, 1.0f, length) / length);
	}
	return vector;
}

Point2 Input::get_mouse_position() const {
	return mouse_pos;
}
Point2 Input::get_last_mouse_speed() {
	mouse_speed_track.update(Vector2());
	return mouse_speed_track.speed;
}

int Input::get_mouse_button_mask() const {
	return mouse_button_mask; // do not trust OS implementation, should remove it - OS::get_singleton()->get_mouse_button_state();
}

void Input::set_mouse_position(const Point2 &p_posf) {
	mouse_pos = p_posf;
}

void Input::warp_mouse_position(const Vector2 &p_to) {
	//OS::get_singleton()->warp_mouse_position(p_to);
}

Point2i Input::warp_mouse_motion(const Ref<InputEventMouseMotion> &p_motion, const Rect2 &p_rect) {
	// The relative distance reported for the next event after a warp is in the boundaries of the
	// size of the rect on that axis, but it may be greater, in which case there's not problem as fmod()
	// will warp it, but if the pointer has moved in the opposite direction between the pointer relocation
	// and the subsequent event, the reported relative distance will be less than the size of the rect
	// and thus fmod() will be disabled for handling the situation.
	// And due to this mouse warping mechanism being stateless, we need to apply some heuristics to
	// detect the warp: if the relative distance is greater than the half of the size of the relevant rect
	// (checked per each axis), it will be considered as the consequence of a former pointer warp.

	const Point2i rel_sgn(p_motion->get_relative().x >= 0.0f ? 1 : -1, p_motion->get_relative().y >= 0.0 ? 1 : -1);
	const Size2i warp_margin = p_rect.size * 0.5f;
	const Point2i rel_warped(
			Math::fmod(p_motion->get_relative().x + rel_sgn.x * warp_margin.x, p_rect.size.x) - rel_sgn.x * warp_margin.x,
			Math::fmod(p_motion->get_relative().y + rel_sgn.y * warp_margin.y, p_rect.size.y) - rel_sgn.y * warp_margin.y);

	const Point2i pos_local = p_motion->get_global_position() - p_rect.position;
	const Point2i pos_warped(Math::fposmod(pos_local.x, p_rect.size.x), Math::fposmod(pos_local.y, p_rect.size.y));
	//if (pos_warped != pos_local) {
	//OS::get_singleton()->warp_mouse_position(pos_warped + p_rect.position);
	//}

	return rel_warped;
}

void Input::action_press(const StringName &p_action, float p_strength) {
	// Create or retrieve existing action.
	Action &action = action_state[p_action];

	action.pressed_idle_frame = Application::get_singleton()->get_idle_frames();
	action.pressed = true;
	action.exact = true;
	action.strength = p_strength;
	action.raw_strength = p_strength;
}

void Input::action_release(const StringName &p_action) {
	// Create or retrieve existing action.
	Action &action = action_state[p_action];

	action.released_idle_frame = Application::get_singleton()->get_idle_frames();
	action.pressed = false;
	action.exact = true;
	action.strength = 0.0f;
	action.raw_strength = 0.0f;
}

Input::CursorShape Input::get_default_cursor_shape() const {
	return default_shape;
}

void Input::set_default_cursor_shape(CursorShape p_shape) {
	if (default_shape == p_shape) {
		return;
	}

	default_shape = p_shape;
	// The default shape is set in Viewport::_gui_input_event. To instantly
	// see the shape in the viewport we need to trigger a mouse motion event.
	Ref<InputEventMouseMotion> mm;
	mm.instance();
	mm->set_position(mouse_pos);
	mm->set_global_position(mouse_pos);
	parse_input_event(mm);
}

Input::CursorShape Input::get_current_cursor_shape() const {
	//return (Input::CursorShape)OS::get_singleton()->get_cursor_shape();
	return CURSOR_ARROW;
}

void Input::set_custom_mouse_cursor(const Ref<Reference> &p_cursor, CursorShape p_shape, const Vector2 &p_hotspot) {
	ERR_FAIL_INDEX(p_shape, Input::CURSOR_MAX);

	//OS::get_singleton()->set_custom_mouse_cursor(p_cursor, (OS::CursorShape)p_shape, p_hotspot);
}

void Input::parse_input_event(const Ref<InputEvent> &p_event) {
	_THREAD_SAFE_METHOD_

	ERR_FAIL_COND(p_event.is_null());

	if (use_accumulated_input) {
		if (buffered_events.empty() || !buffered_events.back()->get()->accumulate(p_event)) {
			buffered_events.push_back(p_event);
		}
	} else if (use_input_buffering) {
		buffered_events.push_back(p_event);
	} else {
		_parse_input_event_impl(p_event, false);
	}
}

void Input::flush_buffered_events() {
	_THREAD_SAFE_METHOD_

	while (buffered_events.front()) {
		// The final delivery of the input event involves releasing the lock.
		// While the lock is released, another thread may lock it and add new events to the back.
		// Therefore, we get each event and pop it while we still have the lock,
		// to ensure the list is in a consistent state.
		List<Ref<InputEvent>>::Element *E = buffered_events.front();
		Ref<InputEvent> e = E->get();
		buffered_events.pop_front();

		_parse_input_event_impl(e, false);
	}
}

bool Input::is_using_input_buffering() {
	return use_input_buffering;
}

void Input::set_use_input_buffering(bool p_enable) {
	use_input_buffering = p_enable;
}

bool Input::is_using_accumulated_input() {
	return use_accumulated_input;
}

void Input::set_use_accumulated_input(bool p_enable) {
	use_accumulated_input = p_enable;
}

void Input::release_pressed_events() {
	flush_buffered_events(); // this is needed to release actions strengths

	keys_pressed.clear();
	physical_keys_pressed.clear();

	for (RBMap<StringName, Input::Action>::Element *E = action_state.front(); E; E = E->next()) {
		if (E->get().pressed) {
			action_release(E->key());
		}
	}
}

void Input::set_main_loop(Application *p_main_loop) {
	main_loop = p_main_loop;
}

void Input::iteration(real_t p_step) {
	if (use_input_buffering || use_accumulated_input) {
		flush_buffered_events();
	}
}

Input::Input() {
	singleton = this;

	use_input_buffering = false;
	use_accumulated_input = true;
	mouse_button_mask = 0;
	main_loop = NULL;
	default_shape = CURSOR_ARROW;
	window_has_focus = true;

	last_mouse_pos_valid = false;
	last_click_ms = 0;
	last_click_button_index = 0;
	last_button_state = 0;

	last_key_modifier_state = 0;
}

unsigned int Input::get_mouse_button_state(unsigned int p_button, int p_action) {
	unsigned int mask = 1 << (p_button - 1);

	if (p_action == GLFW_PRESS) {
		last_button_state |= mask;
	} else {
		last_button_state &= ~mask;
	}

	return last_button_state;
}

void Input::get_key_modifier_state(int mods, Ref<InputEventWithModifiers> state) {
	state->set_shift((mods & GLFW_MOD_SHIFT));
	state->set_control((mods & GLFW_MOD_CONTROL));
	state->set_alt((mods & GLFW_MOD_ALT)); //altgr should not count as alt
	state->set_metakey((mods & GLFW_MOD_SUPER));
}

struct GLFWKeyMap {
	int glfw_code;
	int sfw_code;
} glfw_keymap[] = {
	/* The unknown key */
	{ GLFW_KEY_UNKNOWN, 0 },

	/* Printable keys */
	{ GLFW_KEY_SPACE, KEY_SPACE },
	{ GLFW_KEY_APOSTROPHE, KEY_APOSTROPHE },
	{ GLFW_KEY_COMMA, KEY_COMMA },
	{ GLFW_KEY_MINUS, KEY_MINUS },
	{ GLFW_KEY_PERIOD, KEY_PERIOD },
	{ GLFW_KEY_SLASH, KEY_SLASH },
	{ GLFW_KEY_0, KEY_0 },
	{ GLFW_KEY_1, KEY_1 },
	{ GLFW_KEY_2, KEY_2 },
	{ GLFW_KEY_3, KEY_3 },
	{ GLFW_KEY_4, KEY_4 },
	{ GLFW_KEY_5, KEY_5 },
	{ GLFW_KEY_6, KEY_6 },
	{ GLFW_KEY_7, KEY_7 },
	{ GLFW_KEY_8, KEY_8 },
	{ GLFW_KEY_9, KEY_9 },
	{ GLFW_KEY_SEMICOLON, KEY_SEMICOLON },
	{ GLFW_KEY_EQUAL, KEY_EQUAL },
	{ GLFW_KEY_A, KEY_A },
	{ GLFW_KEY_B, KEY_B },
	{ GLFW_KEY_C, KEY_C },
	{ GLFW_KEY_D, KEY_D },
	{ GLFW_KEY_E, KEY_E },
	{ GLFW_KEY_F, KEY_F },
	{ GLFW_KEY_G, KEY_G },
	{ GLFW_KEY_H, KEY_H },
	{ GLFW_KEY_I, KEY_I },
	{ GLFW_KEY_J, KEY_J },
	{ GLFW_KEY_K, KEY_K },
	{ GLFW_KEY_L, KEY_L },
	{ GLFW_KEY_M, KEY_M },
	{ GLFW_KEY_N, KEY_N },
	{ GLFW_KEY_O, KEY_O },
	{ GLFW_KEY_P, KEY_P },
	{ GLFW_KEY_Q, KEY_Q },
	{ GLFW_KEY_R, KEY_R },
	{ GLFW_KEY_S, KEY_S },
	{ GLFW_KEY_T, KEY_T },
	{ GLFW_KEY_U, KEY_U },
	{ GLFW_KEY_V, KEY_V },
	{ GLFW_KEY_W, KEY_W },
	{ GLFW_KEY_X, KEY_X },
	{ GLFW_KEY_Y, KEY_Y },
	{ GLFW_KEY_Z, KEY_Z },
	{ GLFW_KEY_LEFT_BRACKET, KEY_BRACKETLEFT },
	{ GLFW_KEY_BACKSLASH, KEY_BACKSLASH },
	{ GLFW_KEY_RIGHT_BRACKET, KEY_BRACKETRIGHT },
	{ GLFW_KEY_GRAVE_ACCENT, KEY_QUOTELEFT },
	{ GLFW_KEY_WORLD_1, KEY_EXCLAMDOWN },
	{ GLFW_KEY_WORLD_2, KEY_CENT },

	/* Function keys */
	{ GLFW_KEY_ESCAPE, KEY_ESCAPE },
	{ GLFW_KEY_ENTER, KEY_ENTER },
	{ GLFW_KEY_TAB, KEY_TAB },
	{ GLFW_KEY_BACKSPACE, KEY_BACKSPACE },
	{ GLFW_KEY_INSERT, KEY_INSERT },
	{ GLFW_KEY_DELETE, KEY_DELETE },
	{ GLFW_KEY_RIGHT, KEY_RIGHT },
	{ GLFW_KEY_LEFT, KEY_LEFT },
	{ GLFW_KEY_DOWN, KEY_DOWN },
	{ GLFW_KEY_UP, KEY_UP },
	{ GLFW_KEY_PAGE_UP, KEY_PAGEUP },
	{ GLFW_KEY_PAGE_DOWN, KEY_PAGEDOWN },
	{ GLFW_KEY_HOME, KEY_HOME },
	{ GLFW_KEY_END, KEY_END },
	{ GLFW_KEY_CAPS_LOCK, KEY_CAPSLOCK },
	{ GLFW_KEY_SCROLL_LOCK, KEY_SCROLLLOCK },
	{ GLFW_KEY_NUM_LOCK, KEY_NUMLOCK },
	{ GLFW_KEY_PRINT_SCREEN, KEY_PRINT },
	{ GLFW_KEY_PAUSE, KEY_PAUSE },
	{ GLFW_KEY_F1, KEY_F1 },
	{ GLFW_KEY_F2, KEY_F2 },
	{ GLFW_KEY_F3, KEY_F3 },
	{ GLFW_KEY_F4, KEY_F4 },
	{ GLFW_KEY_F5, KEY_F5 },
	{ GLFW_KEY_F6, KEY_F6 },
	{ GLFW_KEY_F7, KEY_F7 },
	{ GLFW_KEY_F8, KEY_F8 },
	{ GLFW_KEY_F9, KEY_F9 },
	{ GLFW_KEY_F10, KEY_F10 },
	{ GLFW_KEY_F11, KEY_F11 },
	{ GLFW_KEY_F12, KEY_F12 },
	{ GLFW_KEY_F13, KEY_F13 },
	{ GLFW_KEY_F14, KEY_F14 },
	{ GLFW_KEY_F15, KEY_F15 },
	{ GLFW_KEY_F16, KEY_F16 },
	{ GLFW_KEY_F17, 0 },
	{ GLFW_KEY_F18, 0 },
	{ GLFW_KEY_F19, 0 },
	{ GLFW_KEY_F20, 0 },
	{ GLFW_KEY_F21, 0 },
	{ GLFW_KEY_F22, 0 },
	{ GLFW_KEY_F23, 0 },
	{ GLFW_KEY_F24, 0 },
	{ GLFW_KEY_F25, 0 },
	{ GLFW_KEY_KP_0, KEY_KP_0 },
	{ GLFW_KEY_KP_1, KEY_KP_1 },
	{ GLFW_KEY_KP_2, KEY_KP_2 },
	{ GLFW_KEY_KP_3, KEY_KP_3 },
	{ GLFW_KEY_KP_4, KEY_KP_4 },
	{ GLFW_KEY_KP_5, KEY_KP_5 },
	{ GLFW_KEY_KP_6, KEY_KP_6 },
	{ GLFW_KEY_KP_7, KEY_KP_7 },
	{ GLFW_KEY_KP_8, KEY_KP_8 },
	{ GLFW_KEY_KP_9, KEY_KP_9 },
	{ GLFW_KEY_KP_DECIMAL, KEY_KP_PERIOD },
	{ GLFW_KEY_KP_DIVIDE, KEY_KP_DIVIDE },
	{ GLFW_KEY_KP_MULTIPLY, KEY_KP_MULTIPLY },
	{ GLFW_KEY_KP_SUBTRACT, KEY_KP_SUBTRACT },
	{ GLFW_KEY_KP_ADD, KEY_KP_ADD },
	{ GLFW_KEY_KP_ENTER, KEY_KP_ENTER },
	{ GLFW_KEY_KP_EQUAL, KEY_EQUAL },
	{ GLFW_KEY_LEFT_SHIFT, KEY_SHIFT },
	{ GLFW_KEY_LEFT_CONTROL, KEY_CONTROL },
	{ GLFW_KEY_LEFT_ALT, KEY_ALT },
	{ GLFW_KEY_LEFT_SUPER, KEY_SUPER_L },
	{ GLFW_KEY_RIGHT_SHIFT, KEY_SHIFT },
	{ GLFW_KEY_RIGHT_CONTROL, KEY_CONTROL },
	{ GLFW_KEY_RIGHT_ALT, 0 }, //altgr?
	{ GLFW_KEY_RIGHT_SUPER, KEY_SUPER_R },
	{ GLFW_KEY_MENU, KEY_MENU },
	{ 0, 0 },
};

int Input::glfw_to_sfw_code(int glfw_code) {
	for (int i = 0; glfw_keymap[i].glfw_code; i++) {
		if (glfw_keymap[i].glfw_code == glfw_code) {
			return glfw_keymap[i].sfw_code;
		}
	}

	return 0;
}

void Input::GLFWkeyfunCallback(GLFWwindow *window, int glfw_keycode, int scancode, int action, int mods) {
	Input *self = Input::get_singleton();

	self->last_key_modifier_state = mods;

	unsigned int keycode = glfw_to_sfw_code(glfw_keycode);
	unsigned int physical_keycode = keycode;
	unsigned int unicode = scancode;

	bool keypress = action == GLFW_PRESS;
	bool echo = action == GLFW_REPEAT;

	if (physical_keycode == 0 && keycode == 0 && unicode == 0) {
		return;
	}

	if (keycode == 0) {
		keycode = physical_keycode;
	}

	Ref<InputEventKey> k;
	k.instance();

	get_key_modifier_state(mods, k);

	k->set_pressed(keypress);

	if (keycode >= 'a' && keycode <= 'z') {
		keycode -= 'a' - 'A';
	}

	k->set_scancode(keycode);
	k->set_physical_scancode(physical_keycode);
	k->set_unicode(unicode);
	k->set_echo(echo);

	//don't set mod state if modifier keys are released by themselves
	//else event.is_action() will not work correctly here
	if (!k->is_pressed()) {
		if (k->get_scancode() == KEY_SHIFT) {
			k->set_shift(false);
		} else if (k->get_scancode() == KEY_CONTROL) {
			k->set_control(false);
		} else if (k->get_scancode() == KEY_ALT) {
			k->set_alt(false);
		} else if (k->get_scancode() == KEY_META) {
			k->set_metakey(false);
		}
	}

	bool last_is_pressed = Input::get_singleton()->is_key_pressed(k->get_scancode());
	if (k->is_pressed()) {
		if (last_is_pressed) {
			k->set_echo(true);
		}
	}

	self->parse_input_event(k);
}
void Input::GLFWcharfunCallback(GLFWwindow *window, unsigned int codepoint) {
	ERR_PRINT("GLFWcharfunCallback");
}
void Input::GLFWcharmodsfunCallback(GLFWwindow *window, unsigned int codepoint, int mods) {
	ERR_PRINT("GLFWcharmodsfunCallback");
}

void Input::GLFWmousebuttonfunCallback(GLFWwindow *window, int button, int action, int mods) {
	Input *self = Input::get_singleton();

	self->last_key_modifier_state = mods;

	bool pressed = action == GLFW_PRESS;

	Vector2 last_mouse_pos = self->last_mouse_pos;

	Ref<InputEventMouseButton> mb;
	mb.instance();

	get_key_modifier_state(mods, mb);

	mb->set_button_index(button + 1);
	mb->set_button_mask(self->get_mouse_button_state(mb->get_button_index(), action));
	mb->set_position(last_mouse_pos);
	mb->set_global_position(mb->get_position());

	mb->set_pressed(pressed);

	if (pressed) {
		uint64_t diff = STime::time_us() / 1000 - self->last_click_ms;

		if (mb->get_button_index() == self->last_click_button_index) {
			if (diff < 400 && Point2(self->last_click_pos).distance_to(last_mouse_pos) < 5) {
				self->last_click_ms = 0;
				self->last_click_pos = Point2(-100, -100);
				self->last_click_button_index = -1;
				mb->set_doubleclick(true);
			}

		} else if (mb->get_button_index() < 4 || mb->get_button_index() > 7) {
			self->last_click_button_index = mb->get_button_index();
		}

		if (!mb->is_doubleclick()) {
			self->last_click_ms += diff;
			self->last_click_pos = last_mouse_pos;
		}
	}

	self->parse_input_event(mb);
}
void Input::GLFWcursorposfunCallback(GLFWwindow *window, double xpos, double ypos) {
	Input *self = Input::get_singleton();

	Point2 pos(xpos, ypos);

	if (!self->last_mouse_pos_valid) {
		self->last_mouse_pos = pos;
		self->last_mouse_pos_valid = true;
	}

	Point2 rel = pos - self->last_mouse_pos;

	MouseMode mouse_mode = self->get_mouse_mode();

	if (mouse_mode == MOUSE_MODE_CAPTURED) {
		int w = AppWindow::get_singleton()->get_width();
		int h = AppWindow::get_singleton()->get_height();

		pos = Point2i(w / 2, h / 2);
	}

	Ref<InputEventMouseMotion> mm;
	mm.instance();
	mm->set_pressure((self->last_button_state & (1 << (BUTTON_LEFT - 1))) ? 1.0f : 0.0f);

	// Make the absolute position integral so it doesn't look _too_ weird :)
	Point2i posi(pos);

	get_key_modifier_state(self->last_key_modifier_state, mm);
	mm->set_button_mask(self->last_button_state);
	mm->set_position(posi);
	mm->set_global_position(posi);
	mm->set_speed(self->get_last_mouse_speed());

	mm->set_relative(rel);

	self->last_mouse_pos = pos;

	// printf("rel: %d,%d\n", rel.x, rel.y );
	// Don't propagate the motion event unless we have focus
	// this is so that the relative motion doesn't get messed up
	// after we regain focus.
	if (self->window_has_focus || mouse_mode != MOUSE_MODE_CAPTURED) {
		self->parse_input_event(mm);
	}
}
void Input::GLFWcursorenterfunCallback(GLFWwindow *window, int entered) {
	Input *self = Input::get_singleton();

	self->last_mouse_pos_valid = false;

	if (entered) {
		if (self->main_loop && (self->get_mouse_mode() != MOUSE_MODE_CAPTURED)) {
			self->main_loop->notification(Application::NOTIFICATION_WM_MOUSE_ENTER);
		}
	} else {
		if (self->main_loop && (self->get_mouse_mode() != MOUSE_MODE_CAPTURED)) {
			self->main_loop->notification(Application::NOTIFICATION_WM_MOUSE_EXIT);
		}
	}
}
void Input::GLFWscrollfunCallback(GLFWwindow *window, double xoffset, double yoffset) {
	ERR_PRINT("GLFWscrollfunCallback");
}
void Input::GLFWdropfunCallback(GLFWwindow *window, int path_count, const char *paths[]) {
	ERR_PRINT("GLFWdropfunCallback");
}
void Input::GLFWjoystickfunCallback(int jid, int event) {
	ERR_PRINT("GLFWjoystickfunCallback");
}

void Input::GLFWwindowfocusfunCallback(GLFWwindow *window, int focused) {
	Input *self = Input::get_singleton();

	self->window_has_focus = focused;

	if (focused) {
		self->main_loop->notification(Application::NOTIFICATION_WM_FOCUS_IN);
	} else {
		self->release_pressed_events();
		self->main_loop->notification(Application::NOTIFICATION_WM_FOCUS_OUT);
	}
}

void Input::_setup_window_callbacks() {
	GLFWwindow *window = (GLFWwindow *)AppWindow::get_singleton()->get_handle();

	glfwSetKeyCallback(window, &Input::GLFWkeyfunCallback);
	//glfwSetCharCallback(window, &Input::GLFWcharfunCallback);
	//glfwSetCharModsCallback(window, &Input::GLFWcharmodsfunCallback);
	glfwSetMouseButtonCallback(window, &Input::GLFWmousebuttonfunCallback);
	glfwSetCursorPosCallback(window, &Input::GLFWcursorposfunCallback);
	glfwSetCursorEnterCallback(window, &Input::GLFWcursorenterfunCallback);
	//glfwSetScrollCallback(window, &Input::GLFWscrollfunCallback);
	//glfwSetDropCallback(window, &Input::GLFWdropfunCallback);
	//glfwSetJoystickCallback(&Input::GLFWjoystickfunCallback);
	glfwSetWindowFocusCallback(window, &Input::GLFWwindowfocusfunCallback);
}

void Input::_parse_input_event_impl(const Ref<InputEvent> &p_event, bool p_is_emulated) {
	// This function does the final delivery of the input event to user land.
	// Regardless where the event came from originally, this has to happen on the main thread.
	DEV_ASSERT(Thread::get_caller_id() == Thread::get_main_id());

	// Notes on mouse-touch emulation:
	// - Emulated mouse events are parsed, that is, re-routed to this method, so they make the same effects
	//   as true mouse events. The only difference is the situation is flagged as emulated so they are not
	//   emulated back to touch events in an endless loop.
	// - Emulated touch events are handed right to the main loop (i.e., the SceneTree) because they don't
	//   require additional handling by this class.

	Ref<InputEventKey> k = p_event;
	if (k.is_valid() && !k->is_echo() && k->get_scancode() != 0) {
		if (k->is_pressed()) {
			keys_pressed.insert(k->get_scancode());
		} else {
			keys_pressed.erase(k->get_scancode());
		}
	}
	if (k.is_valid() && !k->is_echo() && k->get_physical_scancode() != 0) {
		if (k->is_pressed()) {
			physical_keys_pressed.insert(k->get_physical_scancode());
		} else {
			physical_keys_pressed.erase(k->get_physical_scancode());
		}
	}

	Ref<InputEventMouseButton> mb = p_event;

	if (mb.is_valid()) {
		if (mb->is_pressed()) {
			mouse_button_mask |= (1 << (mb->get_button_index() - 1));
		} else {
			mouse_button_mask &= ~(1 << (mb->get_button_index() - 1));
		}

		Point2 pos = mb->get_global_position();
		if (mouse_pos != pos) {
			set_mouse_position(pos);
		}
	}

	Ref<InputEventMouseMotion> mm = p_event;

	if (mm.is_valid()) {
		Point2 position = mm->get_global_position();
		if (mouse_pos != position) {
			set_mouse_position(position);
		}
		Vector2 relative = mm->get_relative();
		mouse_speed_track.update(relative);
	}

	for (const RBMap<StringName, InputMap::Action>::Element *E = InputMap::get_singleton()->get_action_map().front(); E; E = E->next()) {
		if (InputMap::get_singleton()->event_is_action(p_event, E->key())) {
			Action &action = action_state[E->key()];

			// If not echo and action pressed state has changed
			if (!p_event->is_echo() && is_action_pressed(E->key(), false) != p_event->is_action_pressed(E->key())) {
				if (p_event->is_action_pressed(E->key())) {
					action.pressed = true;
					action.pressed_idle_frame = Application::get_singleton()->get_idle_frames();
				} else {
					action.pressed = false;
					action.released_idle_frame = Application::get_singleton()->get_idle_frames();
				}

				action.strength = 0.0f;
				action.raw_strength = 0.0f;
				action.exact = InputMap::get_singleton()->event_is_action(p_event, E->key(), true);
			}

			action.strength = p_event->get_action_strength(E->key());
			action.raw_strength = p_event->get_action_raw_strength(E->key());
		}
	}

	if (main_loop) {
		_THREAD_SAFE_UNLOCK_
		main_loop->input_event(p_event);
		_THREAD_SAFE_LOCK_
	}
}

String Input::_hex_str(uint8_t p_byte) {
	static const char *dict = "0123456789abcdef";
	char ret[3];
	ret[2] = 0;

	ret[0] = dict[p_byte >> 4];
	ret[1] = dict[p_byte & 0xf];

	return ret;
};

Input *Input::singleton = nullptr;

void Input::SpeedTrack::update(const Vector2 &p_delta_p) {
	uint64_t tick = STime::time_us();
	uint32_t tdiff = tick - last_tick;
	float delta_t = tdiff / 1000000.0;
	last_tick = tick;

	if (delta_t > max_ref_frame) {
		// First movement in a long time, reset and start again.
		speed = Vector2();
		accum = p_delta_p;
		accum_t = 0;
		return;
	}

	accum += p_delta_p;
	accum_t += delta_t;

	if (accum_t < min_ref_frame) {
		// Not enough time has passed to calculate speed precisely.
		return;
	}

	speed = accum / accum_t;
	accum = Vector2();
	accum_t = 0;
}

void Input::SpeedTrack::reset() {
	last_tick = STime::time_us();
	speed = Vector2();
	accum = Vector2();
	accum_t = 0;
}

Input::SpeedTrack::SpeedTrack() {
	min_ref_frame = 0.1;
	max_ref_frame = 3.0;
	reset();
}
