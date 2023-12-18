#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene {
public:
    virtual void event(const SDL_Event &ev) = 0;
    virtual void update(float delta) = 0;
    virtual void render() = 0;

    Scene();
    virtual ~Scene();
};

#endif // APPLICATION_H
