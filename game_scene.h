#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

#include "tile_map.h"
#include "mesh_instance.h"
#include "camera.h"
#include "camera_2d.h"
#include "color_material.h"
#include "colored_material.h"
#include "mesh.h"
#include "sprite.h"
#include "texture.h"
#include "texture_material.h"
#include "texture_material_2d.h"

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
	TextureMaterial2D *material;

	Camera2D *camera_2d;
	TileMap *tile_map;
	Sprite *sprite;

	Camera *camera;
	Mesh *mesh;
	MeshInstance *mi;
	MeshInstance *mi2;
	ColorMaterial *color_material;

	//ColoredMaterial *cmaterial;
};

#endif