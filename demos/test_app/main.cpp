#include "game_application.h"

int main(int argc, char **argv) {
	Application *application = memnew(GameApplication());

	application->start_main_loop();

	memdelete(application);

	return 0;
}
