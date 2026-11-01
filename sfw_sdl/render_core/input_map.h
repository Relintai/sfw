//--STRIP
#ifndef INPUT_MAP_H
#define INPUT_MAP_H
//--STRIP

/*************************************************************************/
/*  input_map.h                                                          */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "render_core/input_event.h"
#include "object/object.h"
#include "core/rb_map.h"
//--STRIP

class InputMap : public Object {
	SFW_OBJECT(InputMap, Object);

public:
	/**
	 * A special value used to signify that a given Action can be triggered by any device
	 */
	static int ALL_DEVICES;

	struct Action {
		int id;
		float deadzone;
		List<Ref<InputEvent>> inputs;
	};

private:
	static InputMap *singleton;

	mutable RBMap<StringName, Action> input_map;

	List<Ref<InputEvent>>::Element *_find_event(Action &p_action, const Ref<InputEvent> &p_event, bool p_exact_match = false, bool *p_pressed = nullptr, float *p_strength = nullptr, float *p_raw_strength = nullptr) const;

	Array _get_action_list(const StringName &p_action);
	Array _get_actions();

public:
	static _FORCE_INLINE_ InputMap *get_singleton() { return singleton; }

	bool has_action(const StringName &p_action) const;
	List<StringName> get_actions() const;
	void add_action(const StringName &p_action, float p_deadzone = 0.5);
	void erase_action(const StringName &p_action);

	float action_get_deadzone(const StringName &p_action);
	void action_set_deadzone(const StringName &p_action, float p_deadzone);
	void action_add_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	bool action_has_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	void action_erase_event(const StringName &p_action, const Ref<InputEvent> &p_event);
	void action_erase_events(const StringName &p_action);

	const List<Ref<InputEvent>> *get_action_list(const StringName &p_action);
	bool event_is_action(const Ref<InputEvent> &p_event, const StringName &p_action, bool p_exact_match = false) const;
	bool event_get_action_status(const Ref<InputEvent> &p_event, const StringName &p_action, bool p_exact_match = false, bool *p_pressed = nullptr, float *p_strength = nullptr, float *p_raw_strength = nullptr) const;

	const RBMap<StringName, Action> &get_action_map() const;
	void load_default();

	String suggest_actions(const StringName &p_action) const;

	InputMap();
};

//--STRIP
#endif // INPUT_MAP_H
//--STRIP
