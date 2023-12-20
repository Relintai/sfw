#include "camera.h"

#include "math_funcs.h"

void Camera::bind() {
	make_current();

	model_view_matrix = Transform();
}

void Camera::make_current() {
	current_camera = this;
}

Camera::Camera() {
	screen_aspect_ratio = 1; //p_viewport_size.width / (float)p_viewport_size.height,

	znear = 0.05;
	zfar = 100;
	size = 1.0;

	vaspect = false;
}
Camera::~Camera() {
}

Camera *Camera::current_camera = NULL;

void OrthographicCamera::bind() {
	Camera::bind();
	projection_matrix.set_orthogonal(
			size,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);
}

OrthographicCamera::OrthographicCamera() :
		Camera() {
}
OrthographicCamera::~OrthographicCamera() {
}

void PerspectiveCamera::bind() {
	Camera::bind();

	projection_matrix.set_perspective(
			fov,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);
}

PerspectiveCamera::PerspectiveCamera() :
		Camera() {
	fov = 70;
}

PerspectiveCamera::~PerspectiveCamera() {
}
