#include "render_objects/mesh_instance_2d.h"

#include "render_objects/camera_2d.h"

void MeshInstance2D::render() {
	if (!mesh) {
		return;
	}

	Transform2D mat_orig = Camera2D::current_camera->get_model_view_matrix();

	Camera2D::current_camera->set_model_view_matrix(mat_orig * transform);

	if (material) {
		material->bind();
	}

	mesh->render();

	for (int i = 0; i < children.size(); ++i) {
		MeshInstance2D *c = children[i];

		if (c) {
			c->render();
		}
	}

	Camera2D::current_camera->set_model_view_matrix(mat_orig);
}

MeshInstance2D::MeshInstance2D() {
	material = NULL;
	mesh = NULL;
}
MeshInstance2D::~MeshInstance2D() {
	children.clear();
}
