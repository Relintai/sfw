#include "mesh_utils.h"

void MeshUtils::create_cone(Mesh *mesh) {
    if (!mesh)
        return;

    uint32_t vc = mesh->vertices.size();

    //eleje
    mesh->add_color(1, 0, 0);
    mesh->add_vertex3(0, 0.5, 0);

    mesh->add_color(1,0,0);
    mesh->add_vertex3(-0.5, -0.5, 0.5);

    mesh->add_color(1, 0, 0);
    mesh->add_vertex3(0.5, -0.5, 0.5);

    mesh->add_triangle(0 + vc, 1 + vc, 2 + vc);

    //bal
    mesh->add_color(0, 1, 0);
    mesh->add_vertex3(0, 0.5, 0);

    mesh->add_color(0, 1, 0);
    mesh->add_vertex3(-0.5, -0.5, -0.5);

    mesh->add_color(0, 1, 0);
    mesh->add_vertex3(-0.5, -0.5, 0.5);

    mesh->add_triangle(3 + vc, 4 + vc, 5 + vc);

    //jobb
    mesh->add_color(0, 0, 1);
    mesh->add_vertex3(0, 0.5, 0);

    mesh->add_color(0, 0, 1);
    mesh->add_vertex3(0.5, -0.5, 0.5);

    mesh->add_color(0, 0, 1);
    mesh->add_vertex3(0.5, -0.5, -0.5);

    mesh->add_triangle(6 + vc, 7 + vc, 8 + vc);

    //hátulja
    mesh->add_color(1, 1, 0);
    mesh->add_vertex3(0, 0.5, 0);

    mesh->add_color(1, 1, 0);
    mesh->add_vertex3(0.5, -0.5, -0.5);

    mesh->add_color(1, 1, 0);
    mesh->add_vertex3(-0.5, -0.5, -0.5);

    mesh->add_triangle(9 + vc, 10 + vc, 11 + vc);

    //alja

    mesh->add_color(1, 0, 1);
    mesh->add_vertex3(-0.5, -0.5, -0.5);

    mesh->add_color(1, 0, 1);
    mesh->add_vertex3(0.5, -0.5, 0.5);

    mesh->add_color(1, 0, 1);
    mesh->add_vertex3(-0.5, -0.5, 0.5);

    mesh->add_color(1, 0, 1);
    mesh->add_vertex3(0.5, -0.5, -0.5);

    mesh->add_triangle(12 + vc, 13 + vc, 14 + vc);
    mesh->add_triangle(13 + vc, 12 + vc, 15 + vc);
}