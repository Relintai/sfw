#include "mesh_instance_3d.h"

#include "camera_3d.h"

void MeshInstance3D::render() {
    if (!mesh) {
        return;
    }

    Transform mat_orig = Camera3D::current_camera->model_view_matrix;

    Camera3D::current_camera->model_view_matrix *= transform;

    if (material) {
        material->bind();
    }

    mesh->render();

    for (uint32_t i = 0; i < children.size(); ++i) {
        MeshInstance3D * c = children[i];

        if (c) {
            c->render();
        }
    }

    Camera3D::current_camera->model_view_matrix = mat_orig;
}

MeshInstance3D::MeshInstance3D() {
    material = NULL;
    mesh = NULL;
}
MeshInstance3D::~MeshInstance3D() {
    children.clear();
}
