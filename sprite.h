#ifndef SPRITE_H
#define SPRITE_H

#include "object_2d.h"

#include "mesh_instance.h"

class Sprite : public Object2D {
public:
    void render();
    void update_mesh();

    Sprite();
    ~Sprite();

    MeshInstance *mesh_instance;

    float width;
    float height;

    float region_x;
    float region_y;
    float region_width;
    float region_height;
};


#endif // SPRITE_H
