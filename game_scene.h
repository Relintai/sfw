#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "camera.h"
#include "mesh_instance.h"
#include "texture.h"
#include "texture_material.h"
#include "tile_map.h"
#include "sprite.h"

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

    Camera *camera;
    Texture *texture;
    TextureMaterial *material;
    TileMap *tile_map;
    Sprite *sprite;
};

#endif