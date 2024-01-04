#include "renderer.h"

#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/material.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
#include "render_core/texture_material_2d.h"
#include "render_core/window.h"

#include "render_core/render_state.h"

void Renderer::draw_point(const Vector2 &p_position, const Color &p_color) {
	//Ugly but oh well
	draw_rect(Rect2(p_position, Vector2(1, 1)), p_color);
}
void Renderer::draw_line(const Vector2 &p_from, const Vector2 &p_to, const Color &p_color, const real_t p_width) {
}
void Renderer::draw_line_rect(const Rect2 &p_rect, const Color &p_color) {
}
void Renderer::draw_rect(const Rect2 &p_rect, const Color &p_color) {
}

void Renderer::draw_texture(const Ref<Texture> &p_texture, const Rect2 &dst_rect, const Color &p_modulate) {
}
void Renderer::draw_texture_clipped(const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate) {
}

void Renderer::draw_mesh_2d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d) {
}
void Renderer::draw_mesh_3d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform &p_transform) {
}

void Renderer::draw_text_2d(const Ref<Font> &p_mesh, const Vector2 &p_position, const Color &p_color) {
}
void Renderer::draw_text_2d_tf(const Ref<Font> &p_mesh, const Transform2D &p_transform_2d, const Color &p_color) {
}
void Renderer::draw_text_2d_tf_material(const Ref<Font> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d) {
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
}
Renderer::~Renderer() {
	_singleton = NULL;
}

Renderer *Renderer::get_singleton() {
	return _singleton;
}

Renderer *Renderer::_singleton = NULL;
