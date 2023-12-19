#ifndef MESH_INSTACE_H
#define MESH_INSTACE_H

#include <vector>

#include "material.h"
#include "mesh.h"

#include "../../libs/glm/vec3.hpp"

class MeshInstance {
public:
    void render();

    MeshInstance();
    ~MeshInstance();

    Material *material;
    Mesh *mesh;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    std::vector<MeshInstance *> children;
};

#endif // MESH_INSTACE_H
