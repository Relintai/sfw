
#include "game_application.h"

int main(int argc, char **argv) {
	Application *application = memnew(GameApplication());

	while (application->running) {
		application->main_loop();
	}

	memdelete(application);

}
