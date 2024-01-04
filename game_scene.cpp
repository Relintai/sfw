#include "game_scene.h"

#include "render_core/application.h"

#include "core/memory.h"
#include "render_core/3rd_glad.h"
#include "render_core/keyboard.h"
#include "render_core/mesh_utils.h"
#include "render_immediate/renderer.h"
//#include "render_core/font.h"

void GameScene::input_event(const Ref<InputEvent> &event) {
	//ERR_PRINT(event->as_text());

	Ref<InputEventKey> k = event;

	if (k.is_valid()) {
		if (k->is_echo()) {
			return;
		}

		uint32_t scancode = k->get_scancode();
		bool pressed = k->is_pressed();

		if (scancode == KEY_W) {
			up = pressed;
		} else if (scancode == KEY_A) {
			left = pressed;
		} else if (scancode == KEY_S) {
			down = pressed;
		} else if (scancode == KEY_D) {
			right = pressed;
		}

		return;
	}

	Ref<InputEventMouseMotion> mm = event;

	if (mm.is_valid()) {
		if (mm->get_button_mask() & BUTTON_MASK_LEFT) {
			tile_map->transform.translate(mm->get_relative());
		}
	}
}

void GameScene::update(float delta) {
	Vector2 trn;

	if (up) {
		trn.y -= delta * 30.0;
	}

	if (down) {
		trn.y += delta * 30.0;
	}

	if (left) {
		trn.x -= delta * 30.0;
	}

	if (right) {
		trn.x += delta * 30.0;
	}

	if (up || down || left || right) {
		sprite->transform.translate(trn);
	}
}

void GameScene::render() {
	//render_obj();
	render_immediate();
}
void GameScene::render_immediate() {
	Renderer *r = Renderer::get_singleton();

	//r->camera_2d_reset();

	r->clear_screen(Color());

	r->draw_point(Vector2(15, 15));
	r->draw_point(Vector2(18, 18), Color(1, 1, 0));

	r->draw_line(Vector2(20, 20), Vector2(80, 20));
	r->draw_line(Vector2(20, 20), Vector2(80, 40));
	r->draw_line(Vector2(20, 30), Vector2(80, 30), Color(1, 1, 0));
	r->draw_line(Vector2(20, 40), Vector2(80, 40), Color(1, 1, 0), 4);
	r->draw_line(Vector2(20, 40), Vector2(80, 60), Color(1, 1, 0), 4);

	r->draw_line_rect(Rect2(100, 100, 40, 40));
	r->draw_line_rect(Rect2(150, 100, 40, 40), Color(1, 1, 0));
	r->draw_line_rect(Rect2(200, 100, 40, 40), Color(1, 1, 1), 4);

	r->draw_rect(Rect2(100, 150, 40, 40));
	r->draw_rect(Rect2(150, 150, 40, 40), Color(1, 1, 0));

	r->draw_texture(texture, Rect2(100, 200, 40, 40));
	r->draw_texture(texture, Rect2(150, 200, 40, 40), Color(1, 0, 0));

	r->draw_texture_clipped(texture, Rect2(20, 20, 30, 30), Rect2(100, 250, 40, 40));
	r->draw_texture_clipped(texture, Rect2(20, 20, 30, 30), Rect2(150, 250, 40, 40), Color(1, 0, 0));

	Transform2D t = Transform2D().rotated(Math_PI / 26.0);

	r->draw_texture_tr(t, texture, Rect2(100, 300, 40, 40));
	r->draw_texture_tr(t, texture, Rect2(150, 300, 40, 40), Color(1, 0, 0));

	r->draw_texture_clipped_tr(t, texture, Rect2(20, 20, 30, 30), Rect2(100, 350, 40, 40));
	r->draw_texture_clipped_tr(t, texture, Rect2(20, 20, 30, 30), Rect2(150, 350, 40, 40), Color(1, 0, 0));

	//r->draw_mesh_2d(sprite->mesh_instance->mesh, texture, Vector2(1000, 500));
	//r->draw_mesh_2d_tr(sprite->mesh_instance->mesh, texture, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1000, 500)));
	//r->draw_mesh_2d_mat(sprite->mesh_instance->mesh, material, Vector2(1000, 500));
	//r->draw_mesh_2d_mat_tr(sprite->mesh_instance->mesh, material, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1000, 600)));

	r->draw_text_2d("draw_text_2d1", _font, Vector2(700, 100));
	r->draw_text_2d("draw_text_2d2", _font, Vector2(800, 100), Color(1, 1, 0));

	r->draw_text_2d_tf("draw_text_2d_tf1", _font, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1000, 500)));
	r->draw_text_2d_tf("draw_text_2d_tf2", _font, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1200, 500)), Color(0, 1, 0));

	r->draw_text_2d_tf_material("draw_text_2d_tf_material1", _font, _font_test_mat, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1000, 800)));
	r->draw_text_2d_tf_material("draw_text_2d_tf_material2", _font, _font_test_mat, Transform2D().rotated(Math_PI / 26.0).translated(Vector2(1200, 800)), Color(1, 0, 0));
}

void GameScene::render_obj() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	static float rot = 0;
	Transform t = camera->get_camera_transform();
	t.basis = Basis(Vector3(0, 1, 0), rot);
	camera->set_camera_transform(t);
	rot += 0.01;

	Ref<Image> d = texture->get_data();
	texture->create_from_image(d);

	camera->bind();

	static float rotmi = 0;
	mi->transform.basis = Basis(Vector3(1, 0, 0), rotmi);
	rotmi += 0.01;
	mi->render();

	camera_2d->bind();
	sprite->render();
	tile_map->render();
	_font_test_sprite->render();
	_font_test_mi->render();

	_text_2d->render();

	//TextRenderer::get_singleton()->font_init();
	//TextRenderer::get_singleton()->font_print("test");
}

GameScene::GameScene() {
	left = false;
	right = false;
	up = false;
	down = false;

	//int w;
	//int h;
	//SDL_GetWindowSize(Application::get_singleton()->window, &w, &h);

	//float ar = static_cast<float>(w) / static_cast<float>(h);
	//camera->width = camera->height * ar;

	_font.instance();
	_font->load_default(31.5);

	_font_test_sprite = memnew(Sprite);

	_font_test_mat.instance();
	_font_test_mat->texture = _font->get_texture();
	_font_test_sprite->mesh_instance->material = _font_test_mat;
	_font_test_sprite->width = _font->get_atlas_width();
	_font_test_sprite->height = _font->get_atlas_height();
	_font_test_sprite->transform.set_origin(Vector2(1000, 100));
	_font_test_sprite->update_mesh();

	_font_test_mesh.instance();
	_font_test_mesh->vertex_dimesions = 2;

	_font_test_mi = memnew(MeshInstance2D());
	_font_test_mi->material = _font_test_mat;
	_font_test_mi->mesh = _font_test_mesh;
	//_font_test_mi->transform.scale(Vector2(10, 10));
	_font_test_mi->transform.set_origin(Vector2(1000, 400));

	_font->generate_mesh("asdfgh\nasdfvb", _font_test_mesh, Color(1, 1, 0));
	_font_test_mesh->upload();

	image.instance();
	image->load_from_file("icon.png");
	//image->bumpmap_to_normalmap();

	texture.instance();
	//texture->load_image("icon.png");
	texture->create_from_image(image);
	//ha a textúrának van alpha csatornája:
	//texture->load_image("download.bmp", GL_RGBA, GL_RGBA);

	material.instance();
	material->texture = texture;

	sprite = new Sprite();
	sprite->mesh_instance->material = material;
	sprite->width = 500;
	sprite->height = 500;
	sprite->transform.set_origin(Vector2(250, 250));
	//sprite->region_x = 7.0 * (1.0 / 16.0);
	//sprite->region_y = 7.0 * (1.0 / 16.0);
	//sprite->region_width = 1.0 / 16.0;
	//sprite->region_height = 1.0 / 16.0;
	sprite->update_mesh();

	tile_map = new TileMap();
	tile_map->material = material;
	tile_map->atlas_size_x = 2;
	tile_map->atlas_size_y = 2;

	tile_map->allocate_data();

	for (int x = 0; x < tile_map->size_x; ++x) {
		for (int y = 0; y < tile_map->size_y; ++y) {
			if (x == 0 || y == 0 || x == tile_map->size_x - 1 || y == tile_map->size_y - 1) {
				tile_map->set_data(x, y, 2);
			} else {
				tile_map->set_data(x, y, 1);
			}
		}
	}

	tile_map->build_mesh();

	tile_map->transform.scale(Vector2(32, 32));
	tile_map->transform.set_origin(Vector2(500, 500));

	camera = new PerspectiveCamera();
	Transform t = camera->get_camera_transform();
	//camera->width = 2;
	//camera->height = 2;
	//camera->position.x = 0;
	//camera->position.y = 0;
	//camera->position.z = -2;
	t.origin.z -= 2;
	camera->set_camera_transform(t);

	camera->screen_aspect_ratio = 1920.0 / 1080.0;

	camera_2d = memnew(Camera2D);
	camera_2d->size = Vector2(1920, 1080);

	mesh = memnew(Mesh());
	//cmaterial = memnew(ColoredMaterial());
	//cmaterial->color = glm::vec4(1, 1, 0, 1);
	color_material.instance();

	//mesh->clear();

	MeshUtils::create_cone(mesh);
	mesh->upload();

	mi = memnew(MeshInstance3D());
	mi->material = color_material.ptr();
	mi->mesh = mesh;

	mi2 = memnew(MeshInstance3D());
	mi2->material = color_material.ptr();
	mi2->mesh = mesh;
	mi2->transform.origin.x = 1;

	mi->children.push_back(mi2);

	//float width = 1;
	//float height = 1;

	//float region_x = 0;
	//float region_y = 0;
	//float region_width = 1;
	//float region_height = 1;

	//float w2 = width / 2.0;
	//float h2 = height / 2.0;

	//mesh->add_uv(region_x, region_y);
	//mesh->add_vertex2(-w2, h2);

	//mesh->add_uv(region_x + region_width, region_y + region_height);
	//mesh->add_vertex2(w2, -h2);

	//mesh->add_uv(region_x, region_y + region_height);
	//mesh->add_vertex2(-w2, -h2);

	//mesh->add_uv(region_x + region_width, region_y);
	//mesh->add_vertex2(w2, h2);

	/*
	mesh->add_vertex2(0, 0.5);
	mesh->add_vertex2(-0.5, -0.5);
	mesh->add_vertex2(0.5, -0.5);

	mesh->add_triangle(0, 1, 2);
	//mesh->add_triangle(0, 1, 3);

	mesh->upload();
	*/

	_text_2d = memnew(Text2D);
	_text_2d->set_font(_font);
	_text_2d->set_text("Test Text2D.\n Newline.");
	_text_2d->set_text_color(Color(1, 1, 0));
	_text_2d->update();
	_text_2d->transform.set_origin(Vector2(1200, 250));

	Renderer::initialize();
}

GameScene::~GameScene() {
	Renderer::destroy();

	memdelete(tile_map);
	memdelete(camera);
	memdelete(sprite);
}
