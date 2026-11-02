//--STRIP
#ifndef GUI_H
#define GUI_H
//--STRIP

//--STRIP
#include "core/int_types.h"
#include "object/object.h"
//--STRIP

union SDL_Event;

class GUI : public Object {
	SFW_OBJECT(GUI, Object);

public:
	static void test();

	static void initialize();
	static void destroy();

	static void new_frame();
	static void render();

	static GUI *get_singleton();

	static void setup_input_hook();
	static void remove_input_hook();

	static void process_event(const SDL_Event *event);

	GUI();
	~GUI();

protected:
	static GUI *_singleton;
};

//--STRIP
#endif // GUI_H
//--STRIP
