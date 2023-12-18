#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "colored_material.h"
#include "camera.h"
#include "mesh.h"
#include "mesh_instance.h"
#include "sprite.h"
#include "texture_material.h"
#include "texture.h"

class GameScene : public Scene {
public:
    virtual void event(const SDL_Event &ev);
    virtual void update(float delta);
    virtual void render();

    GameScene();
    ~GameScene();

    bool left;
    bool right;
    bool up;
    bool down;

    OrthographicCamera *camera;
    Sprite *sprite;
    Texture *texture;
    TextureMaterial *material;
};


#endif // GAME_SCENE_H
