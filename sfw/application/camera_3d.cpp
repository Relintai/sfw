#include "camera_3d.h"

#include "math_funcs.h"

void Camera3D::bind() {
	make_current();

	model_view_matrix = Transform();
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
	Camera3D::bind();
	projection_matrix.set_orthogonal(
			size,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);
}

OrthographicCamera::OrthographicCamera() :
		Camera3D() {
}
OrthographicCamera::~OrthographicCamera() {
}

void PerspectiveCamera::bind() {
	Camera3D::bind();

	projection_matrix.set_perspective(
			fov,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);
}

PerspectiveCamera::PerspectiveCamera() :
		Camera3D() {
	fov = 70;
}

PerspectiveCamera::~PerspectiveCamera() {
}

void FrustumCamera::bind() {
	Camera3D::bind();
}

FrustumCamera::FrustumCamera() :
		Camera3D() {
}

FrustumCamera::~FrustumCamera() {
}
