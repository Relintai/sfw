#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "application.h"
#include "window.h"

#include "game_application.h"
#include "window.h"

Application *application = NULL;

void handle_frame() {
	application->main_loop();
}

int main(int argc, char **argv) {
	AppWindow *w = memnew(AppWindow());
	w->create(100, 0);

	application = new GameApplication();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(handle_frame, 0, 1);
#else

	//while (application->running) {
	//    application->main_loop();
	//}

	while (application->running) {
		if (w->frame_begin()) {
			//w->resize();
			//w->render_callback(loopArg);
			w->frame_end();
			w->frame_swap();
		} else {
			w->shutdown();
		}
	}

	delete application;

#endif // __EMSCRIPTEN__

	return 0;
}
