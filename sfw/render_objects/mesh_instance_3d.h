#ifndef MESH_INSTACE_3D_H
#define MESH_INSTACE_3D_H

//--STRIP
#include "core/vector.h"

#include "render_objects/object_3d.h"

#include "render_core/material.h"
#include "render_core/mesh.h"

#include "core/transform.h"
//--STRIP

class MeshInstance3D : public Object3D {
public:
	void render();

	MeshInstance3D();
	~MeshInstance3D();

	Material *material;
	Mesh *mesh;

	Vector<MeshInstance3D *> children;
};

#endif // MESH_INSTACE_H
