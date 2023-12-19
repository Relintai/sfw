#include "mesh_instance.h"

#include "camera.h"

void MeshInstance::render() {
    if (!mesh) {
        return;
    }

    Transform mat_orig = Camera::current_camera->model_view_matrix;

    Camera::current_camera->model_view_matrix *= transform;

    if (material) {
        material->bind();
    }

    mesh->render();

    for (uint32_t i = 0; i < children.size(); ++i) {
        MeshInstance * c = children[i];

        if (c) {
            c->render();
        }
    }

    Camera::current_camera->model_view_matrix = mat_orig;
}

MeshInstance::MeshInstance() {
    material = NULL;
    mesh = NULL;
}
MeshInstance::~MeshInstance() {
    children.clear();
}
