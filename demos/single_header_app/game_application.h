#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "sfw.h"

class GameApplication : public Application {
	SFW_OBJECT(GameApplication, Application);

public:
	virtual void input_event(const Ref<InputEvent> &event) {
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
	}

	virtual void update(float delta) {
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
			//sprite->transform.translate(trn);
		}
	}

	virtual void render() {
		render_immediate();
	}

	virtual void render_immediate() {
		Renderer *r = Renderer::get_singleton();

		//r->camera_2d_projection_set_to_window();

		r->clear_screen(Color());
		r->camera_2d_projection_set_to_window();

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

	GameApplication() {
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

		_font_test_mat.instance();
		_font_test_mat->texture = _font->get_texture();

		_font_test_mesh.instance();
		_font_test_mesh->vertex_dimesions = 2;

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

		mesh = Ref<Mesh>(memnew(Mesh()));
		//cmaterial = memnew(ColoredMaterial());
		//cmaterial->color = glm::vec4(1, 1, 0, 1);
		color_material.instance();

		//mesh->clear();

		MeshUtils::create_simple_test_cone(mesh);
		mesh->upload();

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

		Renderer::initialize();
	}

	~GameApplication() {
		Renderer::destroy();
	}

	bool left;
	bool right;
	bool up;
	bool down;

	Ref<Image> image;
	Ref<Texture> texture;
	Ref<TextureMaterial2D> material;

	Ref<Font> _font;
	Ref<FontMaterial> _font_test_mat;

	Ref<Mesh> _font_test_mesh;

	Ref<Mesh> mesh;
	Ref<ColorMaterial> color_material;

	//ColoredMaterial *cmaterial;
};

#endif // GAME_APPLICATION_H
