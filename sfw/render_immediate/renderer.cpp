//--STRIP
#include "renderer.h"

#include "render_core/app_window.h"
#include "render_core/color_material.h"
#include "render_core/color_material_2d.h"
#include "render_core/colored_material.h"
#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/material.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
#include "render_core/texture_material.h"
#include "render_core/colored_texture_material_2d.h"

#include "render_core/render_state.h"
//--STRIP

bool Renderer::get_depth_buffer_enable() const {
	return _depth_buffer;
}
void Renderer::set_depth_buffer_enable(const bool p_depth_buffer) {
	_depth_buffer = p_depth_buffer;
}

Renderer::FaceCulling Renderer::get_face_culling() const {
	return _face_culling;
}
void Renderer::set_face_culling(const FaceCulling p_face_culling) {
	if (_face_culling == p_face_culling) {
		return;
	}

	bool were_disabled = _face_culling == FACE_CULLING_OFF;

	_face_culling = p_face_culling;

	switch (p_face_culling) {
		case FACE_CULLING_OFF:
			if (!were_disabled) {
				glDisable(GL_CULL_FACE);
			}

			break;
		case FACE_CULLING_FRONT:
			if (were_disabled) {
				glEnable(GL_CULL_FACE);
			}

			glCullFace(GL_FRONT);
			break;
		case FACE_CULLING_BACK:
			if (were_disabled) {
				glEnable(GL_CULL_FACE);
			}

			glCullFace(GL_BACK);
			break;
		case FACE_CULLING_FRONT_AND_BACK:
			if (were_disabled) {
				glEnable(GL_CULL_FACE);
			}

			glCullFace(GL_FRONT_AND_BACK);
			break;
	}
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
	ERR_FAIL_COND(!p_mesh.is_valid());
	ERR_FAIL_COND(!p_material.is_valid());

	Ref<Mesh> mesh = p_mesh;
	Ref<Material> material = p_material;

	camera_3d_push_model_view_matrix(p_transform);

	material->bind();
	mesh->render();

	camera_3d_pop_model_view_matrix();
}
void Renderer::draw_mesh_3d_colored(const Ref<Mesh> &p_mesh, const Color &p_color, const Transform &p_transform) {
	ERR_FAIL_COND(!p_mesh.is_valid());

	Ref<Mesh> mesh = p_mesh;
	_colored_material_3d->color = p_color;

	camera_3d_push_model_view_matrix(p_transform);

	_colored_material_3d->bind();
	mesh->render();

	camera_3d_pop_model_view_matrix();
}
void Renderer::draw_mesh_3d_vertex_colored(const Ref<Mesh> &p_mesh, const Transform &p_transform) {
	ERR_FAIL_COND(!p_mesh.is_valid());

	Ref<Mesh> mesh = p_mesh;

	camera_3d_push_model_view_matrix(p_transform);

	_color_material_3d->bind();
	mesh->render();

	camera_3d_pop_model_view_matrix();
}
void Renderer::draw_mesh_3d_textured(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Transform &p_transform) {
	ERR_FAIL_COND(!p_mesh.is_valid());
	ERR_FAIL_COND(!p_texture.is_valid());

	_texture_material_3d->texture = p_texture;
	Ref<Mesh> mesh = p_mesh;

	camera_3d_push_model_view_matrix(p_transform);

	_texture_material_3d->bind();
	mesh->render();

	camera_3d_pop_model_view_matrix();
}


void Renderer::camera_2d_bind() {
	RenderState::model_view_matrix_2d = _camera_2d_model_view_matrix;
	RenderState::projection_matrix_2d = _camera_2d_projection_matrix;
}
void Renderer::camera_2d_reset() {
	RenderState::model_view_matrix_2d = Transform2D();
	RenderState::projection_matrix_2d = Transform();

	_camera_2d_model_view_matrix_stack.clear();
	_camera_2d_projection_matrix_stack.clear();

	_camera_2d_projection_matrix = RenderState::projection_matrix_2d;
	_camera_2d_model_view_matrix = RenderState::model_view_matrix_2d;
}

Transform Renderer::camera_2d_get_current_projection_matrix() const {
	return _camera_2d_projection_matrix;
}
void Renderer::camera_2d_push_projection_matrix(const Transform &p_transform) {
	_camera_2d_projection_matrix_stack.push_back(_camera_2d_projection_matrix);

	_camera_2d_projection_matrix *= p_transform;

	RenderState::projection_matrix_2d = _camera_2d_projection_matrix;
}
void Renderer::camera_2d_pop_projection_matrix() {
	if (_camera_2d_projection_matrix_stack.empty()) {
		return;
	}

	_camera_2d_projection_matrix = _camera_2d_projection_matrix_stack[_camera_2d_projection_matrix_stack.size() - 1];

	RenderState::projection_matrix_2d = _camera_2d_projection_matrix;

	_camera_2d_projection_matrix_stack.resize(_camera_2d_projection_matrix_stack.size() - 1);
}
int Renderer::get_camera_2d_projection_matrix_stack_size() const {
	return _camera_2d_projection_matrix_stack.size();
}
void Renderer::camera_2d_projection_matrix_stack_clear() {
	_camera_2d_projection_matrix_stack.clear();
	
	_camera_2d_projection_matrix = Transform();
	RenderState::projection_matrix_2d = _camera_2d_projection_matrix;
}

Transform2D Renderer::camera_2d_get_current_model_view_matrix() const {
	return _camera_2d_model_view_matrix;
}

void Renderer::camera_2d_push_model_view_matrix(const Transform2D &p_transform_2d) {
	_camera_2d_model_view_matrix_stack.push_back(_camera_2d_model_view_matrix);

	_camera_2d_model_view_matrix *= p_transform_2d;

	RenderState::model_view_matrix_2d = _camera_2d_model_view_matrix;
}
void Renderer::camera_2d_pop_model_view_matrix() {
	if (_camera_2d_model_view_matrix_stack.empty()) {
		return;
	}

	_camera_2d_model_view_matrix = _camera_2d_model_view_matrix_stack[_camera_2d_model_view_matrix_stack.size() - 1];

	RenderState::model_view_matrix_2d = _camera_2d_model_view_matrix;

	_camera_2d_model_view_matrix_stack.resize(_camera_2d_model_view_matrix_stack.size() - 1);
}

int Renderer::get_camera_2d_model_view_matrix_stack_size() const {
	return _camera_2d_model_view_matrix_stack.size();
}
void Renderer::camera_2d_model_view_matrix_stack_clear() {
	_camera_2d_model_view_matrix_stack.clear();
	
	_camera_2d_model_view_matrix = Transform2D();
	RenderState::model_view_matrix_2d = _camera_2d_model_view_matrix;
}

void Renderer::camera_2d_projection_set_to_window() {
	Vector2 size = get_window_size();

	Transform canvas_transform;
	canvas_transform.translate_local(-(size.x / 2.0f), -(size.y / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.x, 2.0f / size.y, 1.0f));
	canvas_transform.scale(Vector3(2.0f / size.x, -2.0f / size.y, 1.0f));

	RenderState::projection_matrix_2d = canvas_transform;
	_camera_2d_projection_matrix_stack.clear();
	_camera_2d_projection_matrix = canvas_transform;
}

void Renderer::camera_2d_projection_set_to_size(const Size2i &p_size) {
	Transform canvas_transform;
	canvas_transform.translate_local(-(p_size.x / 2.0f), -(p_size.y / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.x, 2.0f / size.y, 1.0f));
	canvas_transform.scale(Vector3(2.0f / p_size.x, -2.0f / p_size.y, 1.0f));

	RenderState::projection_matrix_2d = canvas_transform;
	_camera_2d_projection_matrix_stack.clear();
	_camera_2d_projection_matrix = canvas_transform;
}

void Renderer::camera_2d_projection_set_to_render_target() {
	Vector2 size = RenderState::render_rect.size;

	Transform canvas_transform;
	canvas_transform.translate_local(-(size.x / 2.0f), -(size.y / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.x, 2.0f / size.y, 1.0f));
	canvas_transform.scale(Vector3(2.0f / size.x, -2.0f / size.y, 1.0f));

	RenderState::projection_matrix_2d = canvas_transform;
	_camera_2d_projection_matrix_stack.clear();
	_camera_2d_projection_matrix = canvas_transform;
}

void Renderer::camera_2d_projection_set_to_transform(const Transform &p_transform) {
	RenderState::projection_matrix_2d = p_transform;
	_camera_2d_projection_matrix_stack.clear();
	_camera_2d_projection_matrix = p_transform;
}

void Renderer::camera_3d_bind() {
	RenderState::camera_transform_3d = _camera_3d_camera_transform_matrix;
	RenderState::model_view_matrix_3d = _camera_3d_model_view_matrix;
	RenderState::projection_matrix_3d = _camera_3d_projection;
}

void Renderer::camera_3d_reset() {
	_camera_3d_projection = Projection();
	_camera_3d_camera_transform_matrix = Transform();
	_camera_3d_model_view_matrix = Transform();
	
	_camera_3d_camera_transform_matrix_stack.clear();
	_camera_3d_model_view_matrix_stack.clear();

	RenderState::camera_transform_3d = _camera_3d_camera_transform_matrix;
	RenderState::model_view_matrix_3d = _camera_3d_model_view_matrix;
	RenderState::projection_matrix_3d = _camera_3d_projection;
}

Transform Renderer::camera_3d_get_current_camera_transform_matrix() const {
	return _camera_3d_camera_transform_matrix;
}
void Renderer::camera_3d_push_camera_transform_matrix(const Transform &p_transform) {
	_camera_3d_camera_transform_matrix_stack.push_back(_camera_3d_camera_transform_matrix);

	_camera_3d_camera_transform_matrix *= p_transform;

	RenderState::camera_transform_3d = _camera_3d_camera_transform_matrix;
}
void Renderer::camera_3d_pop_camera_transform_matrix() {
	if (_camera_3d_camera_transform_matrix_stack.empty()) {
		return;
	}

	_camera_3d_camera_transform_matrix = _camera_3d_camera_transform_matrix_stack[_camera_3d_camera_transform_matrix_stack.size() - 1];

	RenderState::camera_transform_3d = _camera_3d_camera_transform_matrix;

	_camera_3d_camera_transform_matrix_stack.resize(_camera_3d_camera_transform_matrix_stack.size() - 1);
}
int Renderer::get_camera_3d_camera_transform_matrix_stack_size() const {
	return _camera_3d_camera_transform_matrix_stack.size();
}

Transform Renderer::camera_3d_get_current_model_view_matrix() const {
	return _camera_3d_model_view_matrix;
}
void Renderer::camera_3d_push_model_view_matrix(const Transform &p_transform) {
	_camera_3d_model_view_matrix_stack.push_back(_camera_3d_model_view_matrix);

	_camera_3d_model_view_matrix *= p_transform;

	RenderState::model_view_matrix_3d = _camera_3d_model_view_matrix;
}
void Renderer::camera_3d_pop_model_view_matrix() {
	if (_camera_3d_model_view_matrix_stack.empty()) {
		return;
	}

	_camera_3d_model_view_matrix = _camera_3d_model_view_matrix_stack[_camera_3d_model_view_matrix_stack.size() - 1];

	RenderState::model_view_matrix_3d = _camera_3d_model_view_matrix;

	_camera_3d_model_view_matrix_stack.resize(_camera_3d_model_view_matrix_stack.size() - 1);
}
int Renderer::get_camera_3d_model_view_matrix_stack_size() const {
	return _camera_3d_model_view_matrix_stack.size();
}

// Aspect Ratio = w / h
void Renderer::camera_3d_projection_set_to_orthographic(float aspect_ratio, float size, float znear, float zfar, bool vaspect) {
	_camera_3d_projection.set_orthogonal(
			size,
			aspect_ratio,
			znear,
			zfar,
			vaspect);

	RenderState::projection_matrix_3d = _camera_3d_projection;
	
	_last_camera_3d_data.type = LastCamera3DData::TYPE_ORTOGRAPHIC;
	_last_camera_3d_data.size = size;
	_last_camera_3d_data.aspect_ratio = aspect_ratio;
	_last_camera_3d_data.znear = znear;
	_last_camera_3d_data.zfar = zfar;
	_last_camera_3d_data.vaspect = vaspect;
	_last_camera_3d_data.fov = 70;
	_last_camera_3d_data.offset = 0;
}
void Renderer::camera_3d_projection_set_to_perspective(float aspect_ratio, float size, float znear, float zfar, bool vaspect, float fov) {
	_camera_3d_projection.set_perspective(
			fov,
			aspect_ratio,
			znear,
			zfar,
			vaspect);

	RenderState::projection_matrix_3d = _camera_3d_projection;
	
		_last_camera_3d_data.type = LastCamera3DData::TYPE_PERSPECTIVE;
	_last_camera_3d_data.size = size;
	_last_camera_3d_data.aspect_ratio = aspect_ratio;
	_last_camera_3d_data.znear = znear;
	_last_camera_3d_data.zfar = zfar;
	_last_camera_3d_data.vaspect = vaspect;
	_last_camera_3d_data.fov = fov;
	_last_camera_3d_data.offset = 0;
}
void Renderer::camera_3d_projection_set_to_frustum(float aspect_ratio, float size, float znear, float zfar, bool vaspect, float offset) {
	_camera_3d_projection.set_frustum(
			size,
			aspect_ratio,
			offset,
			znear,
			zfar,
			vaspect);

	RenderState::projection_matrix_3d = _camera_3d_projection;
	
	_last_camera_3d_data.type = LastCamera3DData::TYPE_FRUSTUM;
	_last_camera_3d_data.size = size;
	_last_camera_3d_data.aspect_ratio = aspect_ratio;
	_last_camera_3d_data.znear = znear;
	_last_camera_3d_data.zfar = zfar;
	_last_camera_3d_data.vaspect = vaspect;
	_last_camera_3d_data.fov = 70;
	_last_camera_3d_data.offset = offset;
}

Projection Renderer::camera_3d_get_projection_matrix() const {
	return _camera_3d_projection;
}
void Renderer::camera_3d_set_projection_matrix(const Projection &p_projection) {
	_camera_3d_projection = p_projection;

	RenderState::projection_matrix_3d = _camera_3d_projection;
}

Vector3 Renderer::camera_3d_project_ray_normal(const Point2 &p_pos) const {
	Vector3 ray = camera_3d_project_local_ray_normal(p_pos);
	return _camera_3d_camera_transform_matrix.basis.xform(ray).normalized();
};

Vector3 Renderer::camera_3d_project_local_ray_normal(const Point2 &p_pos) const {
	if (_last_camera_3d_data.type == LastCamera3DData::TYPE_ORTOGRAPHIC) {
		return Vector3(0, 0, -1);
	}

	Size2 viewport_size = RenderState::render_rect.size;
	Vector2 cpos = p_pos;
	Vector3 ray;

	Projection cm;
	cm.set_perspective(70, viewport_size.aspect(), _last_camera_3d_data.znear, _last_camera_3d_data.zfar, true);
	Vector2 screen_he = cm.get_viewport_half_extents();
	ray = Vector3(((cpos.x / viewport_size.width) * 2.0 - 1.0) * screen_he.x, ((1.0 - (cpos.y / viewport_size.height)) * 2.0 - 1.0) * screen_he.y, -_last_camera_3d_data.znear).normalized();

	return ray;
};

Vector3 Renderer::camera_3d_project_ray_origin(const Point2 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;
	Vector2 cpos = p_pos;
	ERR_FAIL_COND_V(viewport_size.y == 0, Vector3());

	Vector2 pos = cpos / viewport_size;
	float vsize, hsize;

	vsize = _last_camera_3d_data.size / viewport_size.aspect();
	hsize = _last_camera_3d_data.size;

	Vector3 ray;
	ray.x = pos.x * (hsize)-hsize / 2;
	ray.y = (1.0 - pos.y) * (vsize)-vsize / 2;
	ray.z = -_last_camera_3d_data.znear;
	ray = _camera_3d_camera_transform_matrix.xform(ray);
	return ray;
};

bool Renderer::camera_3d_is_position_behind(const Vector3 &p_pos) const {
	Transform t = _camera_3d_camera_transform_matrix;
	Vector3 eyedir = -t.basis.get_axis(2).normalized();
	return eyedir.dot(p_pos - t.origin) < _last_camera_3d_data.znear;
}

Vector<Vector3> Renderer::camera_3d_get_near_plane_points() const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;
	
	if (_last_camera_3d_data.type == LastCamera3DData::TYPE_ORTOGRAPHIC) {
		cm.set_orthogonal(_last_camera_3d_data.size, viewport_size.aspect(), _last_camera_3d_data.znear, _last_camera_3d_data.zfar, true);
	} else {
		cm.set_perspective(_last_camera_3d_data.fov, viewport_size.aspect(), _last_camera_3d_data.znear, _last_camera_3d_data.zfar, true);
	}

	Vector3 endpoints[8];
	cm.get_endpoints(Transform(), endpoints);

	Vector<Vector3> points;
	points.push_back(Vector3());
	for (int i = 0; i < 4; i++) {
		points.push_back(endpoints[i + 4]);
	}
	return points;
}

Point2 Renderer::camera_3d_unproject_position(const Vector3 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;
	
	if (_last_camera_3d_data.type == LastCamera3DData::TYPE_ORTOGRAPHIC) {
		cm.set_orthogonal(_last_camera_3d_data.size, viewport_size.aspect(), _last_camera_3d_data.znear, _last_camera_3d_data.zfar, true);
	} else {
		cm.set_perspective(_last_camera_3d_data.fov, viewport_size.aspect(), _last_camera_3d_data.znear, _last_camera_3d_data.zfar, true);
	}

	Plane p(_camera_3d_camera_transform_matrix.xform_inv(p_pos), 1.0);

	p = cm.xform(p);
	p.normal /= p.d;

	Point2 res;
	res.x = (p.normal.x * 0.5 + 0.5) * viewport_size.x;
	res.y = (-p.normal.y * 0.5 + 0.5) * viewport_size.y;

	return res;
}


Vector3 Renderer::camera_3d_project_position(const Point2 &p_point, float p_z_depth) const {
	if (p_z_depth == 0) {
		return _camera_3d_camera_transform_matrix.origin;
	}
	
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;
	
	if (_last_camera_3d_data.type == LastCamera3DData::TYPE_ORTOGRAPHIC) {
		cm.set_orthogonal(_last_camera_3d_data.size, viewport_size.aspect(), p_z_depth, _last_camera_3d_data.zfar, true);
	} else {
		cm.set_perspective(_last_camera_3d_data.fov, viewport_size.aspect(), p_z_depth, _last_camera_3d_data.zfar, true);
	}

	Vector2 vp_he = cm.get_viewport_half_extents();

	Vector2 point;
	point.x = (p_point.x / viewport_size.x) * 2.0 - 1.0;
	point.y = (1.0 - (p_point.y / viewport_size.y)) * 2.0 - 1.0;
	point *= vp_he;

	Vector3 p(point.x, point.y, -p_z_depth);

	return _camera_3d_camera_transform_matrix.xform(p);
}


void Renderer::clear_screen(const Color &p_color) {
	glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);

	if (!_depth_buffer) {
		glClear(GL_COLOR_BUFFER_BIT);
	} else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
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
	_face_culling = FACE_CULLING_OFF;

	_2d_mesh.instance();
	_2d_mesh->vertex_dimesions = 2;
	_3d_mesh.instance();
	_font_mesh.instance();
	_font_mesh->vertex_dimesions = 2;

	_texture_material_2d.instance();
	_font_material.instance();
	_color_material_2d.instance();

	_texture_material_3d.instance();
	_color_material_3d.instance();
	_colored_material_3d.instance();
}
Renderer::~Renderer() {
	_singleton = NULL;
}

Renderer *Renderer::get_singleton() {
	return _singleton;
}

Renderer *Renderer::_singleton = NULL;
