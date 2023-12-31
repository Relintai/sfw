/*************************************************************************/
/*  shortcut.cpp                                                         */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

#include "shortcut.h"

#include "core/render_core/input_event.h"

void ShortCut::set_shortcut(const Ref<InputEvent> &p_shortcut) {
	shortcut = p_shortcut;
	emit_changed();
}

Ref<InputEvent> ShortCut::get_shortcut() const {
	return shortcut;
}

bool ShortCut::is_shortcut(const Ref<InputEvent> &p_event) const {
	return shortcut.is_valid() && shortcut->shortcut_match(p_event);
}

String ShortCut::get_as_text() const {
	if (shortcut.is_valid()) {
		return shortcut->as_text();
	} else {
		return "None";
	}
}

bool ShortCut::is_valid() const {
	return shortcut.is_valid();
}

ShortCut::ShortCut() {
}

ShortCut::~ShortCut() {
}