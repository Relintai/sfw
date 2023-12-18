#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>

#include <SDL.h>

#include "opengl.h"
#include "scene.h"

class Application {
public:
    bool running;
    int target_fps;

    virtual void event(const SDL_Event &ev);
    virtual void update(float delta);
    virtual void render();

    void main_loop();

    Application();
    virtual ~Application();

    Scene *scene;

    SDL_Window *window;
    SDL_GLContext context;

    static Application *get_singleton();

    double frame_delta;

protected:
    static Application * _instance;
};

#endif // APPLICATION_H
