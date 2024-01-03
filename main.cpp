#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "game_application.h"

Application *application = NULL;

void handle_frame() {
	application->core_loop();
}

int main(int argc, char **argv) {
	application = memnew(GameApplication());

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(handle_frame, 0, 1);
#else

	while (application->running) {
		application->core_loop();
	}

#endif // __EMSCRIPTEN__

	memdelete(application);

	return 0;
}
