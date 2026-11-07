#include "game_application.h"

#include <SDL3/SDL_main.h>

int main(int argc, char **argv) {
	Application *application = memnew(GameApplication());

	application->start_main_loop();

	memdelete(application);

	return 0;
}
