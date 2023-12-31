#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>

#include "render_core/scene.h"

class AppWindow;

class Application {
public:
    bool running;
    int target_fps;

    virtual void event();
    virtual void update(float delta);
    virtual void render();

    void main_loop();

    Application();
    virtual ~Application();

    Scene *scene;

    AppWindow *window;

    static Application *get_singleton();

    double frame_delta;

protected:
    static Application * _instance;
};

#endif // APPLICATION_H
