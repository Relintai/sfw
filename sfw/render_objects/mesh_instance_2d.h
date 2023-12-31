#ifndef MESH_INSTACE_2D_H
#define MESH_INSTACE_2D_H

#include "core/vector.h"

#include "render_core/material.h"
#include "render_core/mesh.h"

#include "core/transform.h"

class MeshInstance2D {
public:
    void render();

    MeshInstance2D();
    ~MeshInstance2D();

    Material *material;
    Mesh *mesh;

    Transform2D transform;

   Vector<MeshInstance2D *> children;
};

#endif // MESH_INSTACE_H
