#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "application.h"

#include "game_application.h"

Application *application = NULL;

void handle_frame() {
    application->main_loop();
}

int main(int argc, char** argv)
{
    application = new GameApplication();

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(handle_frame, 0, 1);
    #else

    while (application->running) {
        application->main_loop();
    }

    delete application;

    #endif // __EMSCRIPTEN__

    return 0;
}
