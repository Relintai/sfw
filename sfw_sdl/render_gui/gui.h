//--STRIP
#ifndef GUI_H
#define GUI_H
//--STRIP

//--STRIP
#include "core/int_types.h"
#include "object/object.h"
//--STRIP

class GUI : public Object {
	SFW_OBJECT(GUI, Object);

public:
	static void test();

	static void initialize();
	static void destroy();

	static void new_frame();
	static void render();

	static GUI *get_singleton();

	GUI();
	~GUI();

protected:
	static GUI *_singleton;
};

//--STRIP
#endif // GUI_H
//--STRIP
