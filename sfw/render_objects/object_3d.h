#ifndef OBJECT_3D_H
#define OBJECT_3D_H

//--STRIP
#include "object/object.h"

#include "core/transform.h"
//--STRIP

class Object3D : public Object {
	SFW_OBJECT(Object3D, Object);

public:
	Object3D();
	virtual ~Object3D();

	Transform transform;
};

#endif // OBJECT_3D_h
