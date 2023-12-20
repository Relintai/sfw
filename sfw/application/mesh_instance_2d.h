#ifndef MESH_INSTACE_2D_H
#define MESH_INSTACE_2D_H

#include <vector>

#include "material.h"
#include "mesh.h"

#include "transform.h"

class MeshInstance2D {
public:
    void render();

    MeshInstance2D();
    ~MeshInstance2D();

    Material *material;
    Mesh *mesh;

    Transform2D transform;

    std::vector<MeshInstance2D *> children;
};

#endif // MESH_INSTACE_H
