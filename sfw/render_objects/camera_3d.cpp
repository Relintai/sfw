#include "render_objects/camera_3d.h"

#include "core/math_funcs.h"

#include "render_core/render_state.h"

Transform Camera3D::get_camera_transform() {
	return _camera_transform;
}
void Camera3D::set_camera_transform(const Transform &p_value) {
	_camera_transform = p_value;

	if (current_camera == this) {
		RenderState::camera_transform_3d = _camera_transform;
	}
}

Transform Camera3D::get_model_view_matrix() {
	return _model_view_matrix;
}
void Camera3D::set_model_view_matrix(const Transform &p_value) {
	_model_view_matrix = p_value;

	if (current_camera == this) {
		RenderState::model_view_matrix_3d = _model_view_matrix;
	}
}

Projection Camera3D::get_projection_matrix() {
	return _projection_matrix;
}
void Camera3D::set_projection_matrix(const Projection &p_value) {
	_projection_matrix = p_value;

	if (current_camera == this) {
		RenderState::projection_matrix_3d = _projection_matrix;
	}
}

void Camera3D::bind() {
	make_current();

	_model_view_matrix = Transform();

	RenderState::camera_transform_3d = _camera_transform;
	RenderState::model_view_matrix_3d = _model_view_matrix;
	RenderState::projection_matrix_3d = _projection_matrix;
}

void Camera3D::make_current() {
	current_camera = this;
}

Camera3D::Camera3D() {
	screen_aspect_ratio = 1; //p_viewport_size.width / (float)p_viewport_size.height,

	znear = 0.05;
	zfar = 100;
	size = 1.0;

	vaspect = false;
}
Camera3D::~Camera3D() {
}

Camera3D *Camera3D::current_camera = NULL;

void OrthographicCamera::bind() {
	_projection_matrix.set_orthogonal(
			size,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

OrthographicCamera::OrthographicCamera() :
		Camera3D() {
}
OrthographicCamera::~OrthographicCamera() {
}

void PerspectiveCamera::bind() {
	_projection_matrix.set_perspective(
			fov,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

PerspectiveCamera::PerspectiveCamera() :
		Camera3D() {
	fov = 70;
}

PerspectiveCamera::~PerspectiveCamera() {
}

void FrustumCamera::bind() {
	_projection_matrix.set_frustum(
			size,
			screen_aspect_ratio,
			offset,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

FrustumCamera::FrustumCamera() :
		Camera3D() {
	offset = 0;

	_projection_matrix.set_frustum(
			size,
			screen_aspect_ratio,
			offset,
			znear,
			zfar,
			vaspect);
}

FrustumCamera::~FrustumCamera() {
}
