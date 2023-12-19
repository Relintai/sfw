#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "application.h"

#include "game_scene.h"
#include "window.h"

class GameApplication : public Application {
public:
    GameApplication() : Application() {
        scene = new GameScene();

        AppWindow *w = memnew(AppWindow());
        w->create(100, 0);
    }

    ~GameApplication() {
        delete scene;
    }
};


#endif // GAME_APPLICATION_H
