//--STRIP
#ifndef SPRITE_H
#define SPRITE_H
//--STRIP

//--STRIP
#include "render_objects/object_2d.h"

#include "core/transform_2d.h"
#include "render_objects/mesh_instance_2d.h"
//--STRIP

class Sprite : public Object2D {
public:
    void render();
    void update_mesh();

    Sprite();
    ~Sprite();

    Transform2D transform;

    MeshInstance2D *mesh_instance;

    float width;
    float height;

    float region_x;
    float region_y;
    float region_width;
    float region_height;
};

//--STRIP
#endif // SPRITE_H
//--STRIP
