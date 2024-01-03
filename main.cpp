#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "game_application.h"

int main(int argc, char **argv) {
	Application *application = memnew(GameApplication());

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(&Application::core_loop_static, 0, 1);
#else
	while (application->running) {
		application->core_loop();
	}
#endif // __EMSCRIPTEN__

	memdelete(application);

	return 0;
}
