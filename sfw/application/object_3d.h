#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "transform.h"

class Object3D {
public:
    Object3D();
    virtual ~Object3D();

    Transform transform;
};


#endif // OBJECT_3D_h
