#include "object_2d.h"


Object2D::Object2D() {
    position = glm::vec2(0, 0);
    rotation = 0;
    scale = glm::vec2(1, 1);
}

Object2D::~Object2D() {
}
