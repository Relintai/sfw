#ifndef MESH_INSTACE_3D_H
#define MESH_INSTACE_3D_H

#include <vector>

#include "object_3d.h"

#include "material.h"
#include "mesh.h"

#include "transform.h"

class MeshInstance3D : public Object3D {
public:
	void render();

	MeshInstance3D();
	~MeshInstance3D();

	Material *material;
	Mesh *mesh;

	std::vector<MeshInstance3D *> children;
};

#endif // MESH_INSTACE_H
