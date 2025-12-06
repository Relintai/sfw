#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "sfw.h"

class Thread;
class Socket;

class GameScene : public Scene {
	SFW_OBJECT(GameScene, Scene);

public:
	enum RenderTypes {
		RENDER_TYPE_MAX = 16
	};

	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();
	virtual void render_immediate(bool clear_screen = true);
	virtual void render_obj();
	virtual void render_immediate_3d(bool clear_screen = true);
	virtual void render_gui(bool clear_screen = true);
	virtual void render_gui_manual(bool clear_screen = true);

	void toggle_thread();
	static void test_thread_func(void *d);

	void toggle_socket();
	static void socket_thread_func(void *d);

	GameScene();
	~GameScene();

	int render_type;

	bool left;
	bool right;
	bool up;
	bool down;

	Thread *_thread;
	bool _thread_running;

	bool _socket_thread_running;
	Thread *_server_socket_thread;
	Socket *_server_socket;

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

	Ref<Mesh> _mesh_utils_test;
	MeshInstance3D *_mesh_utils_test_mi;

	Ref<FrameBuffer> _frame_buffer;
	Ref<RenderTexture> _render_tex;

	Signal test_signal;

	//ColoredMaterial *cmaterial;
};

#endif
