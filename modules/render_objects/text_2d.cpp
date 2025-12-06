//--STRIP
#include "render_objects/text_2d.h"

#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/mesh.h"
#include "render_objects/camera_2d.h"
//--STRIP

Color Text2D::get_text_color() const {
	return _text_color;
}
void Text2D::set_text_color(const Color &p_color) {
	_text_color = p_color;
}

String Text2D::get_text() const {
	return _text;
}
void Text2D::set_text(const String &p_text) {
	_text = p_text;
}

Ref<Font> Text2D::get_font() const {
	return _font;
}
void Text2D::set_font(const Ref<Font> &p_font) {
	_font = p_font;

	if (_font.is_valid()) {
		_material->texture = _font->get_texture();
	}
}

Vector2 Text2D::get_text_size() {
	return _text_size;
}

void Text2D::update() {
	_mesh->clear();

	if (!_font.is_valid()) {
		return;
	}

	_text_size = _font->generate_mesh(_text, _mesh, _text_color);

	_mesh->upload();
}

void Text2D::render() {
	Transform2D mat_orig = Camera2D::current_camera->get_model_view_matrix();

	Camera2D::current_camera->set_model_view_matrix(mat_orig * transform);

	_material->bind();
	_mesh->render();

	Camera2D::current_camera->set_model_view_matrix(mat_orig);
}

Text2D::Text2D() {
	_material.instance();
	_mesh.instance();
	_mesh->vertex_dimesions = 2;
}
Text2D::~Text2D() {
}
