#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "render_objects/object_2d.h"

#include "render_core/mesh.h"

#include "render_core/material.h"

class TileMap : public Object2D {
    public:

    void build_mesh();
    void allocate_data();
    void add_rect(const int x, const int y, const float uv_x, const float uv_y, const float uv_size_x, const float uv_size_y);

    uint8_t get_data(const int x, const int y) const;
    void set_data(const int x, const int y, const uint8_t value);

    void render();

    TileMap();
    ~TileMap();

    uint8_t *data;
    int size_x;
    int size_y;

    int atlas_size_x;
    int atlas_size_y;

    Mesh *mesh;
    Material *material;
};

#endif
