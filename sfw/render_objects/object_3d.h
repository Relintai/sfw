#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "object/object.h"

#include "core/transform.h"

class Object3D : public Object {
	SFW_OBJECT(Object3D, Object);

public:
	Object3D();
	virtual ~Object3D();

	Transform transform;
};

#endif // OBJECT_3D_h
