/*************************************************************************/
/*  rect2i.cpp                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/rect2i.h"
#include "core/ustring.h"
//--STRIP

Rect2i::operator String() const {
	return "[P: " + position.operator String() + ", S: " + size + "]";
}
