#ifndef MESH_INSTACE_H
#define MESH_INSTACE_H

#include <vector>

#include "material.h"
#include "mesh.h"

#include "transform.h"

class MeshInstance {
public:
    void render();

    MeshInstance();
    ~MeshInstance();

    Material *material;
    Mesh *mesh;

    Transform transform;

    std::vector<MeshInstance *> children;
};

#endif // MESH_INSTACE_H
