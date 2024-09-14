//--STRIP
#ifndef GUI_H
#define GUI_H
//--STRIP

//--STRIP
#include "core/int_types.h"
#include <stdio.h>

#include "object/object.h"
#include "object/reference.h"
//--STRIP

class GUI : public Object {
	SFW_OBJECT(GUI, Object);

public:
	static void initialize();
	static void destroy();

	static void new_frame();
	static void render();

	static void test();

	static GUI *get_singleton();

	GUI();
	~GUI();

protected:
	static GUI *_singleton;

};

//--STRIP
#endif // GUI_H
//--STRIP
