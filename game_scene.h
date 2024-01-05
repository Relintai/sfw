#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "render_core/scene.h"

#include "render_core/color_material.h"
#include "render_core/colored_material.h"
#include "render_core/font.h"
#include "render_core/image.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
#include "render_core/texture_material.h"
#include "render_core/texture_material_2d.h"
#include "render_objects/camera_2d.h"
#include "render_objects/camera_3d.h"
#include "render_objects/mesh_instance_2d.h"
#include "render_objects/mesh_instance_3d.h"
#include "render_objects/sprite.h"
#include "render_objects/text_2d.h"
#include "render_objects/tile_map.h"

class GameScene : public Scene {
	SFW_OBJECT(GameScene, Scene);

public:
	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();
	virtual void render_immediate();
	virtual void render_obj();

	GameScene();
	~GameScene();

	bool left;
	bool right;
	bool up;
	bool down;

	Ref<Image> image;
	Ref<Texture> texture;
	Ref<TextureMaterial2D> material;

	Ref<Font> _font;
	Sprite *_font_test_sprite;
	Ref<FontMaterial> _font_test_mat;

	Ref<Mesh> _font_test_mesh;
	MeshInstance2D *_font_test_mi;

	Camera2D *camera_2d;
	TileMap *tile_map;
	Sprite *sprite;

	Camera3D *camera;
	Ref<Mesh> mesh;
	MeshInstance3D *mi;
	MeshInstance3D *mi2;
	Ref<ColorMaterial> color_material;

	Text2D *_text_2d;

	//ColoredMaterial *cmaterial;
};

#endif