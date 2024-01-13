//--STRIP
#ifndef SHORTCUT_H
#define SHORTCUT_H
//--STRIP

/*************************************************************************/
/*  shortcut.h                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "object/resource.h"
//--STRIP

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

//--STRIP
#endif // SHORTCUT_H
//--STRIP
