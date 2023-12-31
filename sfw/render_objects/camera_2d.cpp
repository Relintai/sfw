#include "render_objects/camera_2d.h"

#include "core/math_funcs.h"

void Camera2D::bind() {
	make_current();

	Transform canvas_transform;
	canvas_transform.translate_local(-(size.width / 2.0f), -(size.height / 2.0f), 0.0f);
	//canvas_transform.scale(Vector3(2.0f / size.width, 2.0f / size.height, 1.0f));
	canvas_transform.scale(Vector3(2.0f / size.width, -2.0f / size.height, 1.0f));
	projection_matrix = canvas_transform;

	model_view_matrix = Transform2D();
}

void Camera2D::make_current() {
	current_camera = this;
}

Camera2D::Camera2D() {
}
Camera2D::~Camera2D() {
}

Camera2D *Camera2D::current_camera = NULL;
