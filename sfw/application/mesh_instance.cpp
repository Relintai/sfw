#include "mesh_instance.h"

#include "camera.h"

#include "./libs/glm/vec3.hpp"
#include "./libs/glm/matrix.hpp"
#include "./libs/glm/gtc/matrix_transform.hpp"


void MeshInstance::render() {
    if (!mesh) {
        return;
    }

    glm::mat4 mat_orig = Camera::current_camera->model_view_matrix;

    Camera::current_camera->model_view_matrix = glm::translate(Camera::current_camera->model_view_matrix, position);

    Camera::current_camera->model_view_matrix = glm::rotate(Camera::current_camera->model_view_matrix, rotation.x, glm::vec3(1, 0, 0));
    Camera::current_camera->model_view_matrix = glm::rotate(Camera::current_camera->model_view_matrix, rotation.y, glm::vec3(0, 1, 0));
    Camera::current_camera->model_view_matrix = glm::rotate(Camera::current_camera->model_view_matrix, rotation.z, glm::vec3(0, 0, 1));

    Camera::current_camera->model_view_matrix = glm::scale(Camera::current_camera->model_view_matrix, scale);


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

    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}
MeshInstance::~MeshInstance() {
    children.clear();
}
