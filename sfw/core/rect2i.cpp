/*************************************************************************/
/*  rect2i.cpp                                                           */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
//--STRIP

Rect2i::operator String() const {
	return "[P: " + position.operator String() + ", S: " + size + "]";
}
