#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "application.h"

#include "game_application.h"

//érdekesség
//https://gist.github.com/reduz/9635c731f0592d7e526367c6063b8f8f
//https://gist.github.com/reduz/9b9d1278848237fd9a9a8b6cc77c8270
//https://github.com/reduz/larvita3

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
