#ifndef OBJECT_2D_H
#define OBJECT_2D_H

//--STRIP
#include "object/object.h"

#include "core/transform_2d.h"
//--STRIP

class Object2D : public Object {
    SFW_OBJECT(Object2D, Object);

public:
    Object2D();
    virtual ~Object2D();

    Transform2D transform;
};


#endif // OBJECT_2D_h
