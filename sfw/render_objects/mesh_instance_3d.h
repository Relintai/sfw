//--STRIP
#ifndef MESH_INSTACE_3D_H
#define MESH_INSTACE_3D_H
//--STRIP

//--STRIP
#include "core/vector.h"

#include "render_objects/object_3d.h"

#include "render_core/material.h"
#include "render_core/mesh.h"

#include "core/transform.h"
//--STRIP

class MeshInstance3D : public Object3D {
	SFW_OBJECT(MeshInstance3D, Object3D);

public:
	void render();

	MeshInstance3D();
	~MeshInstance3D();

	Ref<Material> material;
	Ref<Mesh> mesh;

	Vector<MeshInstance3D *> children;
};

//--STRIP
#endif // MESH_INSTACE_H
//--STRIP
