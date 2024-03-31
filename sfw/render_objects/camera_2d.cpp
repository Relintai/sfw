//--STRIP
#include "render_objects/camera_2d.h"

#include "core/math_funcs.h"

#include "render_core/render_state.h"
//--STRIP

Transform2D Camera2D::get_model_view_matrix() {
	return _model_view_matrix;
}
void Camera2D::set_model_view_matrix(const Transform2D &p_value) {
	_model_view_matrix = p_value;

	if (current_camera == this) {
		RenderState::model_view_matrix_2d = _model_view_matrix;
	}
}

Transform Camera2D::get_projection_matrix() {
	return _projection_matrix;
}
void Camera2D::set_projection_matrix(const Transform &p_value) {
	_projection_matrix = p_value;

	if (current_camera == this) {
		RenderState::projection_matrix_2d = _projection_matrix;
	}
}

void Camera2D::bind() {
	make_current();

	Transform canvas_transform;
	canvas_transform.translate_local(-(size.width / 2.0f), -(size.height / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.width, 2.0f / size.height, 1.0f));
	canvas_transform.scale(Vector3(2.0f / size.width, -2.0f / size.height, 1.0f));

	_projection_matrix = canvas_transform;
	_model_view_matrix = Transform2D();

	RenderState::model_view_matrix_2d = _model_view_matrix;
	RenderState::projection_matrix_2d = _projection_matrix;
}

void Camera2D::make_current() {
	current_camera = this;
}



Camera2D::Camera2D() {
}
Camera2D::~Camera2D() {
}

Camera2D *Camera2D::current_camera = NULL;
