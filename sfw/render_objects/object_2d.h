//--STRIP
#ifndef OBJECT_2D_H
#define OBJECT_2D_H
//--STRIP

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

//--STRIP
#endif // OBJECT_2D_h
//--STRIP
