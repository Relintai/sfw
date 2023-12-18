#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    virtual void event() = 0;
    virtual void update(float delta) = 0;
    virtual void render() = 0;

    Scene();
    virtual ~Scene();
};

#endif // APPLICATION_H
