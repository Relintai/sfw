#ifndef MESH_UTILS_H
#define MESH_UTILS_H

//--STRIP
#include "render_core/mesh.h"
//--STRIP

class MeshUtils {
public:
	static void create_cone(Ref<Mesh> mesh);

    /*
	static void create_capsule(Array &p_arr, float radius, float mid_height, int radial_segments = 64, int rings = 8);
	static void create_cube(Array &p_arr, Vector3 size, int subdivide_w = 0, int subdivide_h = 0, int subdivide_d = 0);
	static void create_cylinder(Array &p_arr, float top_radius, float bottom_radius, float height, int radial_segments = 64, int rings = 4);
	static void create_plane(Array &p_arr, Size2 size = Size2(2.0, 2.0), int subdivide_w = 0, int subdivide_d = 0, Vector3 center_offset = Vector3(0.0, 0.0, 0.0));
	static void create_prism(Array &p_arr, float left_to_right = 0.5, Vector3 size = Vector3(2.0, 2.0, 2.0), int subdivide_w = 0, int subdivide_h = 0, int subdivide_d = 0);
	static void create_quad(Array &p_arr, Size2 size = Size2(1.0, 1.0), Vector3 center_offset = Vector3(0.0, 0.0, 0.0));
	static void create_sphere(Array &p_arr, float radius, float height, int radial_segments = 64, int rings = 32, bool is_hemisphere = false);
	static void create_point(Array &p_arr);
    */
};

#endif
