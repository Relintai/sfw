#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

/*

#include "mesh_instance.h"
#include "sprite.h"
#include "texture.h"
#include "texture_material.h"
#include "tile_map.h"
*/

#include "colored_material.h"
#include "mesh.h"
#include "camera.h"
#include "texture.h"
#include "texture_material.h"
#include "camera.h"
#include "sprite.h"


class GameScene : public Scene {
public:
	virtual void event();
	virtual void update(float delta);
	virtual void render();

	GameScene();
	~GameScene();
	/*
	bool left;
	bool right;
	bool up;
	bool down;
	*/

	Texture *texture;
	TextureMaterial *material;
	//TileMap *tile_map;
	Sprite *sprite;

	Camera *camera;
	Mesh *mesh;
	ColoredMaterial *cmaterial;
};

#endif