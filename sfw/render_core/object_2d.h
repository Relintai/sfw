#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "transform_2d.h"

class Object2D {
public:
    Object2D();
    virtual ~Object2D();

    Transform2D transform;
};


#endif // OBJECT_2D_h
