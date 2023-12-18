#include "camera.h"

#include "./libs/glm/gtc/matrix_transform.hpp"


void Camera::bind() {
    make_current();

    model_view_matrix = glm::mat4(1);
}

void Camera::make_current() {
    current_camera = this;
}

Camera::Camera() {
    width = 2;
    height = 2;
    fov = glm::radians(45.0);

    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}
Camera::~Camera() {
}

Camera* Camera::current_camera = NULL;

void OrthographicCamera::bind() {
    Camera::bind();

    projection_matrix = glm::ortho<float>(-(width / 2.0),
                                          width / 2.0,
                                          -(height / 2.0),
                                          height / 2.0);

    projection_matrix = glm::translate(projection_matrix, -position);

    projection_matrix = glm::rotate(projection_matrix, rotation.x, glm::vec3(1, 0, 0));
    projection_matrix = glm::rotate(projection_matrix, rotation.y, glm::vec3(0, 1, 0));
    projection_matrix = glm::rotate(projection_matrix, rotation.z, glm::vec3(0, 0, 1));

    projection_matrix = glm::scale(projection_matrix, scale);
}

OrthographicCamera::OrthographicCamera() : Camera() {
}
OrthographicCamera::~OrthographicCamera() {
}

void PerspectiveCamera::bind() {
    Camera::bind();

    projection_matrix = glm::perspectiveFov<float>(fov, width, height, near, far);

    projection_matrix = glm::translate(projection_matrix, -position);

    projection_matrix = glm::rotate(projection_matrix, rotation.x, glm::vec3(1, 0, 0));
    projection_matrix = glm::rotate(projection_matrix, rotation.y, glm::vec3(0, 1, 0));
    projection_matrix = glm::rotate(projection_matrix, rotation.z, glm::vec3(0, 0, 1));

    projection_matrix = glm::scale(projection_matrix, scale);
}

PerspectiveCamera::PerspectiveCamera() : Camera() {
    near = 0.1;
    far = 10;
}

PerspectiveCamera::~PerspectiveCamera() {
}

