#include "game_scene.h"

#include "render_core/application.h"

#include "core/inet_address.h"
#include "core/memory.h"
#include "core/sfw_time.h"
#include "core/socket.h"
#include "core/thread.h"
#include "render_core/3rd_glad.h"
#include "render_core/app_window.h"
#include "render_core/keyboard.h"
#include "render_core/mesh_utils.h"
#include "render_gui/gui.h"
#include "render_gui/imgui.h"
#include "render_immediate/renderer.h"
//#include "render_core/font.h"
#include "core/os.h"
#include "core/sub_process.h"

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

		if (k->get_physical_scancode() == KEY_SPACE) {
			if (pressed) {
				++render_type;

				if (render_type >= RENDER_TYPE_MAX) {
					render_type = 0;
				}
			}
		}

		if (k->get_physical_scancode() == KEY_K) {
			if (pressed) {
				image->save_png("test_image_save.png");
				image->save_bmp("test_image_save.bmp");
				image->save_tga("test_image_save.tga");
				image->save_jpg("test_image_save.jpg", 70);

				Ref<Image> fimage = image->duplicate();
				fimage->convert(Image::FORMAT_RGBAF);
				fimage->save_hdr("test_image_save.hdr");

				Ref<Image> timg = texture->get_data();

				timg->save_png("timg.png");

				ERR_PRINT("Test images Saved!");
			}
		}

		if (k->get_physical_scancode() == KEY_T) {
			if (pressed) {
				toggle_thread();
			}
		}

		if (k->get_physical_scancode() == KEY_P) {
			if (pressed) {
				toggle_socket();
			}
		}

		if (k->get_physical_scancode() == KEY_H) {
			if (pressed) {
				ERR_PRINT("Running Game");
				SubProcess s;
				ERR_PRINT(itos(s.run("game")));
			}
		}

		if (k->get_physical_scancode() == KEY_S) {
			if (pressed) {
				ERR_PRINT("Sending test signal");
				test_signal.emit(this);
				test_signal.emit(this, 12);
				test_signal.emit(this, 33, "Test String");
			}
		}

		if (k->get_physical_scancode() == KEY_I) {
			if (pressed) {
				ERR_PRINT("SFWTime::get_date().day: " + String::num(SFWTime::get_date().day));
				ERR_PRINT("SFWTime::get_date(true).day: " + String::num(SFWTime::get_date(true).day));
				ERR_PRINT("SFWTime::get_time().hour: " + String::num(SFWTime::get_time().hour));
				ERR_PRINT("SFWTime::get_time(true).hour: " + String::num(SFWTime::get_time(true).hour));
				ERR_PRINT("SFWTime::get_time_zone_info().name: " + (SFWTime::get_time_zone_info().name));

				ERR_PRINT("SFWTime::get_iso_date_time(): " + SFWTime::get_iso_date_time());
				ERR_PRINT("SFWTime::get_iso_date_time(true): " + SFWTime::get_iso_date_time(true));

				ERR_PRINT("SFWTime::get_unix_time(): " + String::num(SFWTime::get_unix_time()));
				ERR_PRINT("SFWTime::get_system_time_secs(): " + String::num(SFWTime::get_system_time_secs()));
				ERR_PRINT("SFWTime::get_system_time_msecs(): " + String::num(SFWTime::get_system_time_msecs()));
			}
		}

		return;
	}

	/*
	Ref<InputEventMouseMotion> mm = event;

	if (mm.is_valid()) {
		if (mm->get_button_mask() & BUTTON_MASK_LEFT) {
			tile_map->transform.translate(mm->get_relative());
		}
	}
	*/
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
		//sprite->transform.translate(trn);
	}
}

void GameScene::render() {
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	AppWindow::get_singleton()->reset_viewport();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float rotmi = 0;

	if (render_type == 0) {
		render_immediate();
	} else if (render_type == 1) {
		_mesh_utils_test->clear();
		MeshUtils::create_simple_test_cone(_mesh_utils_test);
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 2) {
		_mesh_utils_test->clear();
		MeshUtils::create_capsule(_mesh_utils_test, 0.5, 0.5);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 3) {
		_mesh_utils_test->clear();
		MeshUtils::create_cube(_mesh_utils_test, Vector3(0.5, 0.5, 0.5));
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 4) {
		_mesh_utils_test->clear();
		MeshUtils::create_cylinder(_mesh_utils_test, 0.2, 0.5, 1);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 5) {
		_mesh_utils_test->clear();
		MeshUtils::create_plane(_mesh_utils_test);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 6) {
		_mesh_utils_test->clear();
		MeshUtils::create_prism(_mesh_utils_test);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 7) {
		_mesh_utils_test->clear();
		MeshUtils::create_quad(_mesh_utils_test);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 8) {
		_mesh_utils_test->clear();
		MeshUtils::create_quad_with_indices(_mesh_utils_test);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 9) {
		_mesh_utils_test->clear();
		MeshUtils::create_sphere(_mesh_utils_test, 0.5, 0.5);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 10) {
		_mesh_utils_test->clear();
		MeshUtils::create_point(_mesh_utils_test);
		_mesh_utils_test->fill_colors_interpolated(Color(0.2, 0, 0), Color(1, 0, 0));
		_mesh_utils_test->upload();

		Renderer *r = Renderer::get_singleton();
		r->camera_3d_bind();
		Transform t = Transform(Basis(Vector3(1, 0, 0), rotmi), Vector3());
		rotmi += 0.01;
		r->draw_mesh_3d_vertex_colored(_mesh_utils_test, t);
	} else if (render_type == 11) {
		render_immediate_3d();
	} else if (render_type == 12) {
		Renderer *r = Renderer::get_singleton();
		r->set_face_culling(Renderer::FACE_CULLING_BACK);

		Vector2i render_tex_size = _render_tex->get_size();

		_frame_buffer->bind();
		_frame_buffer->set_as_viewport();

		r->camera_2d_projection_set_to_size(render_tex_size);
		r->clear_screen(Color());

		r->camera_3d_bind();
		r->camera_3d_projection_set_to_perspective(_frame_buffer->get_aspect());

		render_immediate_3d(false);

		render_immediate(false);

		_render_tex->update();
		_frame_buffer->unbind();

		_frame_buffer->reset_as_viewport();

		r->camera_2d_projection_set_to_window();
		r->clear_screen(Color(1, 0, 0));
		r->draw_texture(_render_tex, Rect2(100, 100, render_tex_size.x, render_tex_size.y));
	} else if (render_type == 13) {
		render_gui();
	} else if (render_type == 14) {
		render_gui_manual();
	}
}
void GameScene::render_immediate(bool clear_screen) {
	Renderer *r = Renderer::get_singleton();

	if (clear_screen) {
		r->clear_screen(Color());
		r->camera_2d_projection_set_to_window();
	}

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

void GameScene::render_immediate_3d(bool clear_screen) {
	Renderer *r = Renderer::get_singleton();

	if (clear_screen) {
		r->clear_screen(Color());
		r->camera_2d_projection_set_to_window();

		r->camera_3d_bind();
		r->camera_3d_projection_set_to_perspective(AppWindow::get_singleton()->get_aspect());
	}

	static float rotmi = 0;

	_mesh_utils_test->clear();
	MeshUtils::create_simple_test_cone(_mesh_utils_test);
	_mesh_utils_test->upload();

	Transform tf;
	tf.basis = Basis(Vector3(1, 0, 0), rotmi);
	tf.origin.z -= 2;

	r->draw_mesh_3d_vertex_colored(_mesh_utils_test, tf);

	rotmi += 0.01;
}

void GameScene::render_gui(bool clear_screen) {
	Renderer *r = Renderer::get_singleton();

	if (clear_screen) {
		r->clear_screen(Color());
		r->camera_2d_projection_set_to_window();

		r->camera_3d_bind();
		r->camera_3d_projection_set_to_perspective(AppWindow::get_singleton()->get_aspect());
	}

	GUI::new_frame();
	GUI::test();
	GUI::render();
}

void GameScene::render_gui_manual(bool clear_screen) {
	Renderer *r = Renderer::get_singleton();

	if (clear_screen) {
		r->clear_screen(Color());
		r->camera_2d_projection_set_to_window();

		r->camera_3d_bind();
		r->camera_3d_projection_set_to_perspective(AppWindow::get_singleton()->get_aspect());
	}

	GUI::new_frame();

	ImGuiIO &io = ImGui::GetIO();
	(void)io;

	// Our state
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world! This is an another demo!"); // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window) {
		ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	GUI::render();
}

void GameScene::toggle_thread() {
	if (_thread) {
		_thread_running = false;

		_thread->wait_to_finish();

		memdelete(_thread);
		_thread = NULL;
	} else {
		_thread_running = true;

		_thread = memnew(Thread);
		_thread->start(test_thread_func, this);
	}
}

void GameScene::test_thread_func(void *data) {
	GameScene *self = (GameScene *)data;

	while (self->_thread_running) {
		ERR_PRINT("Test Thread!");
	}
}

void GameScene::toggle_socket() {
	static bool sockets_inited = false;
	if (!sockets_inited) {
		// This will make the windows popup appear where it asks for permission to communicate
		// Without this Sockets won't work on windows.
		Socket::global_init();
	}

	if (_server_socket) {
		_socket_thread_running = false;

		_server_socket_thread->wait_to_finish();

		memdelete(_server_socket_thread);
		_server_socket_thread = NULL;
	} else {
		_socket_thread_running = true;

		_server_socket_thread = memnew(Thread);
		_server_socket_thread->start(socket_thread_func, this);
	}
}
void GameScene::socket_thread_func(void *data) {
	GameScene *self = (GameScene *)data;

	self->_server_socket = memnew(Socket);

	InetAddress addr(8080);

	self->_server_socket->create_net_socket();
	self->_server_socket->set_non_block();
	self->_server_socket->bind_address(addr);
	self->_server_socket->listen();

	ERR_PRINT("TEST SERVER IS LISTENING on http://127.0.0.1:8080");

	Vector<Socket *> client_sockets;

	//https://stackoverflow.com/questions/40448937/socket-recv-buffer-size
	char buffer[8192];

	Socket *client_socket = memnew(Socket);

	while (self->_socket_thread_running) {
		int a = self->_server_socket->accept(client_socket);

		if (a != -1) {
			ERR_PRINT("New connection! " + itos(a));

			client_sockets.push_back(client_socket);
			client_socket = memnew(Socket());
		}

		for (int i = 0; i < client_sockets.size(); ++i) {
			Socket *s = client_sockets[i];

			int l = s->read(buffer, 8192);

			if (l > 0) {
				String request = String::utf8(buffer, l);

				ERR_PRINT("Read!\n");
				ERR_PRINT(request);
				ERR_PRINT("Sending answer!\n");

				String content = "Your browser sent the following request:<br><br>";
				content += request.newline_to_br();

				String resp;
				resp += "HTTP/1.1 200 OK\n";
				resp += "Connection: Close\n";
				resp += "Content-Type: text/html\n";
				resp += "Content-Length: " + itos(content.utf8().size()) + "\n";
				resp += "\n";
				resp += content;

				CharString cs = resp.utf8();

				s->send(cs.get_data(), cs.size());

				s->close_write();
				memdelete(s);
				client_sockets.remove(i);
				--i;
			}
		}
	}

	for (int i = 0; i < client_sockets.size(); ++i) {
		memdelete(client_sockets[i]);
	}

	client_sockets.clear();

	memdelete(client_socket);

	self->_server_socket->close_write();

	memdelete(self->_server_socket);
	self->_server_socket = NULL;
}

void GameScene::signal_member(Signal *emitter) {
	LOG_MSG("signal_member Params:");
	for (int i = 0; i < emitter->params.size(); ++i) {
		LOG_MSG(String(emitter->params[i]));
	}
	LOG_MSG("signal_member Params End.");
}
void GameScene::signal_static(Signal *emitter) {
	LOG_MSG("signal_static Params:");
	for (int i = 0; i < emitter->params.size(); ++i) {
		LOG_MSG(String(emitter->params[i]));
	}
	LOG_MSG("signal_static Params End.");
}

GameScene::GameScene() {
	render_type = 0;

	_thread_running = false;
	_thread = NULL;

	_socket_thread_running = false;
	_server_socket_thread = NULL;
	_server_socket = NULL;

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

	/*
	_font_test_sprite = memnew(Sprite);

	_font_test_sprite->mesh_instance->material = _font_test_mat;
	_font_test_sprite->width = _font->get_atlas_width();
	_font_test_sprite->height = _font->get_atlas_height();
	_font_test_sprite->transform.set_origin(Vector2(1000, 100));
	_font_test_sprite->update_mesh();
	*/

	_font_test_mesh.instance();
	_font_test_mesh->vertex_dimesions = 2;

	/*
	_font_test_mi = memnew(MeshInstance2D());
	_font_test_mi->material = _font_test_mat;
	_font_test_mi->mesh = _font_test_mesh;
	//_font_test_mi->transform.scale(Vector2(10, 10));
	_font_test_mi->transform.set_origin(Vector2(1000, 400));
	*/

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

	_mesh_utils_test.instance();

	Renderer::initialize();
	GUI::initialize();

	_frame_buffer.instance();
	_frame_buffer->create(960, 540);

	_render_tex.instance();
	_render_tex->set_frame_buffer(_frame_buffer);

	test_signal.connect(this, &GameScene::signal_member);
	test_signal.connect_static(&GameScene::signal_static);

	ERR_PRINT("Processor count: " + String::num(OS::get_processor_count()));
}

GameScene::~GameScene() {
	GUI::destroy();
	Renderer::destroy();
}
