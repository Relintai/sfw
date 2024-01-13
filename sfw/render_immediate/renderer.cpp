//--STRIP
#include "renderer.h"

#include "render_core/color_material_2d.h"
#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/material.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
#include "render_core/texture_material_2d.h"
#include "render_core/app_window.h"

#include "render_core/render_state.h"
//--STRIP

bool Renderer::get_depth_buffer_enable() const {
	return _depth_buffer;
}
void Renderer::set_depth_buffer_enable(const bool p_depth_buffer) {
	_depth_buffer = p_depth_buffer;
}

void Renderer::draw_point(const Vector2 &p_position, const Color &p_color) {
	//Ugly but oh well
	draw_rect(Rect2(p_position, Vector2(1, 1)), p_color);
}
void Renderer::draw_line(const Vector2 &p_from, const Vector2 &p_to, const Color &p_color, const real_t p_width) {
	_2d_mesh->clear();

	Vector2 offset = (p_from - p_to).rotated(Math_PI / 2.0).normalized();
	offset *= p_width / 2.0;

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_from.x - offset.x, p_from.y - offset.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_to.x + offset.x, p_to.y + offset.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_to.x - offset.x, p_to.y - offset.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_from.x + offset.x, p_from.y + offset.y);

	//mesh->add_vertex2(-w2, -h2);
	//mesh->add_vertex2(w2, h2);
	//mesh->add_vertex2(-w2, h2);
	//mesh->add_vertex2(w2, -h2);

	_2d_mesh->add_triangle(1, 0, 2);
	_2d_mesh->add_triangle(0, 1, 3);

	_2d_mesh->upload();

	_color_material_2d->bind();
	_2d_mesh->render();
}
void Renderer::draw_line_rect(const Rect2 &p_rect, const Color &p_color, const real_t p_width) {
	Vector2 rect_end = p_rect.get_end();

	//Ugly but oh well
	draw_line(p_rect.position, Vector2(rect_end.x, p_rect.position.y), p_color, p_width);
	draw_line(p_rect.position, Vector2(p_rect.position.x, rect_end.y), p_color, p_width);
	draw_line(rect_end, Vector2(rect_end.x, p_rect.position.y), p_color, p_width);
	draw_line(rect_end, Vector2(p_rect.position.x, rect_end.y), p_color, p_width);
}
void Renderer::draw_rect(const Rect2 &p_rect, const Color &p_color) {
	_2d_mesh->clear();

	Vector2 rect_end = p_rect.get_end();

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_rect.position.x, p_rect.position.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(rect_end.x, rect_end.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(p_rect.position.x, rect_end.y);

	_2d_mesh->add_color(p_color);
	_2d_mesh->add_vertex2(rect_end.x, p_rect.position.y);

	_2d_mesh->add_triangle(1, 0, 2);
	_2d_mesh->add_triangle(0, 1, 3);

	_2d_mesh->upload();

	_color_material_2d->bind();
	_2d_mesh->render();
}

void Renderer::draw_texture(const Ref<Texture> &p_texture, const Rect2 &p_dst_rect, const Color &p_modulate) {
	_2d_mesh->clear();

	Vector2 rect_end = p_dst_rect.get_end();

	_2d_mesh->add_uv(0, 0);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(p_dst_rect.position.x, p_dst_rect.position.y);

	_2d_mesh->add_uv(1, 1);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(rect_end.x, rect_end.y);

	_2d_mesh->add_uv(0, 1);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(p_dst_rect.position.x, rect_end.y);

	_2d_mesh->add_uv(1, 0);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(rect_end.x, p_dst_rect.position.y);

	_2d_mesh->add_triangle(1, 0, 2);
	_2d_mesh->add_triangle(0, 1, 3);

	_2d_mesh->upload();

	_texture_material_2d->texture = p_texture;
	_texture_material_2d->bind();
	_2d_mesh->render();
}
void Renderer::draw_texture_clipped(const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate) {
	_2d_mesh->clear();

	Rect2 uv = Rect2(0, 0, 1, 1);

	if (p_texture.is_valid()) {
		Vector2 ts = p_texture->get_size();

		Vector2 ss = p_src_rect.position;
		Vector2 se = p_src_rect.get_end();

		uv.position.x = ss.x / ts.x;
		uv.position.x = ss.y / ts.y;
		uv.size.x = se.x / ts.x;
		uv.size.x = se.y / ts.y;
	}

	Vector2 rect_end = p_dst_rect.get_end();

	_2d_mesh->add_uv(uv.position.x, uv.position.y);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(p_dst_rect.position.x, p_dst_rect.position.y);

	_2d_mesh->add_uv(uv.size.x, uv.size.y);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(rect_end.x, rect_end.y);

	_2d_mesh->add_uv(uv.position.x, uv.size.y);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(p_dst_rect.position.x, rect_end.y);

	_2d_mesh->add_uv(uv.size.x, uv.position.y);
	_2d_mesh->add_color(p_modulate);
	_2d_mesh->add_vertex2(rect_end.x, p_dst_rect.position.y);

	_2d_mesh->add_triangle(1, 0, 2);
	_2d_mesh->add_triangle(0, 1, 3);

	_2d_mesh->upload();

	_texture_material_2d->texture = p_texture;
	_texture_material_2d->bind();
	_2d_mesh->render();
}

void Renderer::draw_texture_tr(const Transform2D &p_transform_2d, const Ref<Texture> &p_texture, const Rect2 &p_dst_rect, const Color &p_modulate) {
	camera_2d_push_model_view_matrix(p_transform_2d);
	draw_texture(p_texture, p_dst_rect, p_modulate);
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_texture_clipped_tr(const Transform2D &p_transform_2d, const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate) {
	camera_2d_push_model_view_matrix(p_transform_2d);
	draw_texture_clipped(p_texture, p_src_rect, p_dst_rect, p_modulate);
	camera_2d_pop_model_view_matrix();
}

void Renderer::draw_mesh_2d(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Vector2 &p_position) {
	ERR_FAIL_COND(!p_mesh.is_valid());

	_texture_material_2d->texture = p_texture;
	Ref<Mesh> mesh = p_mesh;

	camera_2d_push_model_view_matrix(Transform2D().translated(p_position));

	_texture_material_2d->bind();
	mesh->render();
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_mesh_2d_tr(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Transform2D &p_transform_2d) {
	ERR_FAIL_COND(!p_mesh.is_valid());

	_texture_material_2d->texture = p_texture;
	Ref<Mesh> mesh = p_mesh;

	camera_2d_push_model_view_matrix(p_transform_2d);

	_texture_material_2d->bind();

	mesh->render();
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_mesh_2d_mat(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Vector2 &p_position) {
	ERR_FAIL_COND(!p_mesh.is_valid());
	ERR_FAIL_COND(!p_material.is_valid());

	Ref<Material> material = p_material;
	Ref<Mesh> mesh = p_mesh;

	camera_2d_push_model_view_matrix(Transform2D().translated(p_position));

	material->bind();

	mesh->render();
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_mesh_2d_mat_tr(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d) {
	ERR_FAIL_COND(!p_mesh.is_valid());
	ERR_FAIL_COND(!p_material.is_valid());

	Ref<Material> material = p_material;
	Ref<Mesh> mesh = p_mesh;

	camera_2d_push_model_view_matrix(p_transform_2d);

	material->bind();

	mesh->render();
	camera_2d_pop_model_view_matrix();
}

void Renderer::draw_text_2d(const String &p_text, const Ref<Font> &p_font, const Vector2 &p_position, const Color &p_color) {
	ERR_FAIL_COND(!p_font.is_valid());

	_font_mesh->clear();
	p_font->generate_mesh(p_text, _font_mesh, p_color);
	_font_mesh->upload();

	_font_material->texture = p_font->get_texture();

	camera_2d_push_model_view_matrix(Transform2D().translated(p_position));

	_font_material->bind();

	_font_mesh->render();
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_text_2d_tf(const String &p_text, const Ref<Font> &p_font, const Transform2D &p_transform_2d, const Color &p_color) {
	camera_2d_push_model_view_matrix(p_transform_2d);
	draw_text_2d(p_text, p_font, Vector2(), p_color);
	camera_2d_pop_model_view_matrix();
}
void Renderer::draw_text_2d_tf_material(const String &p_text, const Ref<Font> &p_font, const Ref<Material> &p_material, const Transform2D &p_transform_2d, const Color &p_color) {
	ERR_FAIL_COND(!p_font.is_valid());
	ERR_FAIL_COND(!p_material.is_valid());

	_font_mesh->clear();
	p_font->generate_mesh(p_text, _font_mesh, p_color);
	_font_mesh->upload();

	Ref<Material> material = p_material;

	camera_2d_push_model_view_matrix(p_transform_2d);

	material->bind();

	_font_mesh->render();
	camera_2d_pop_model_view_matrix();
}

void Renderer::draw_mesh_3d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform &p_transform) {
}

Transform2D Renderer::camera_2d_get_current_model_view_matrix() const {
	return RenderState::model_view_matrix_2d;
}

void Renderer::camera_2d_push_model_view_matrix(const Transform2D &p_transform_2d) {
	camera_2d_model_view_matrix_stack.push_back(RenderState::model_view_matrix_2d);

	RenderState::model_view_matrix_2d *= p_transform_2d;
}
void Renderer::camera_2d_pop_model_view_matrix() {
	if (camera_2d_model_view_matrix_stack.empty()) {
		return;
	}

	RenderState::model_view_matrix_2d = camera_2d_model_view_matrix_stack[camera_2d_model_view_matrix_stack.size() - 1];
	camera_2d_model_view_matrix_stack.resize(camera_2d_model_view_matrix_stack.size() - 1);
}

int Renderer::get_camera_2d_model_view_matrix_stack_size() const {
	return camera_2d_model_view_matrix_stack.size();
}

void Renderer::camera_2d_reset() {
	Vector2 size = get_window_size();

	Transform canvas_transform;
	canvas_transform.translate_local(-(size.x / 2.0f), -(size.y / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.x, 2.0f / size.y, 1.0f));
	canvas_transform.scale(Vector3(2.0f / size.x, -2.0f / size.y, 1.0f));

	RenderState::model_view_matrix_2d = Transform2D();
	RenderState::projection_matrix_2d = canvas_transform;

	camera_2d_model_view_matrix_stack.clear();
}

void Renderer::camera_3d_reset() {
}

void Renderer::clear_screen(const Color &p_color) {
	glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);

	if (!_depth_buffer) {
		glClear(GL_COLOR_BUFFER_BIT);
	} else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//? Make it manual?
	camera_2d_reset();
}

Vector2i Renderer::get_window_size() const {
	return Vector2i(AppWindow::get_singleton()->get_width(), AppWindow::get_singleton()->get_height());
}

float Renderer::get_window_aspect() const {
	return AppWindow::get_singleton()->get_aspect();
}

void Renderer::initialize() {
	ERR_FAIL_COND(_singleton);

	memnew(Renderer);
}
void Renderer::destroy() {
	ERR_FAIL_COND(!_singleton);

	memdelete(_singleton);
}

Renderer::Renderer() {
	_singleton = this;

	_depth_buffer = false;

	_2d_mesh.instance();
	_2d_mesh->vertex_dimesions = 2;
	_3d_mesh.instance();
	_font_mesh.instance();
	_font_mesh->vertex_dimesions = 2;

	_texture_material_2d.instance();
	_font_material.instance();
	_color_material_2d.instance();
}
Renderer::~Renderer() {
	_singleton = NULL;
}

Renderer *Renderer::get_singleton() {
	return _singleton;
}

Renderer *Renderer::_singleton = NULL;
