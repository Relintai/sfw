#ifndef SHORTCUT_H
#define SHORTCUT_H

/*************************************************************************/
/*  shortcut.h                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "object/resource.h"

class InputEvent;

class ShortCut : public Resource {
	SFW_OBJECT(ShortCut, Resource);

public:
	void set_shortcut(const Ref<InputEvent> &p_shortcut);
	Ref<InputEvent> get_shortcut() const;
	bool is_shortcut(const Ref<InputEvent> &p_event) const;
	bool is_valid() const;

	String get_as_text() const;

	ShortCut();
	~ShortCut();

private:
	Ref<InputEvent> shortcut;
};

#endif // SHORTCUT_H
