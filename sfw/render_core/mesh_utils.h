//--STRIP
#ifndef MESH_UTILS_H
#define MESH_UTILS_H
//--STRIP

//--STRIP
#include "render_core/mesh.h"
//--STRIP

class MeshUtils {
public:
	static void create_simple_test_cone(Ref<Mesh> mesh);
	static void create_capsule(Ref<Mesh> mesh, float radius, float mid_height, int radial_segments = 64, int rings = 8);
	static void create_cube(Ref<Mesh> mesh, Vector3 size, int subdivide_w = 0, int subdivide_h = 0, int subdivide_d = 0);
	static void create_cylinder(Ref<Mesh> mesh, float top_radius, float bottom_radius, float height, int radial_segments = 64, int rings = 4);
	static void create_plane(Ref<Mesh> mesh, Size2 size = Size2(2.0, 2.0), int subdivide_w = 0, int subdivide_d = 0, Vector3 center_offset = Vector3(0.0, 0.0, 0.0));
	static void create_prism(Ref<Mesh> mesh, float left_to_right = 0.5, Vector3 size = Vector3(2.0, 2.0, 2.0), int subdivide_w = 0, int subdivide_h = 0, int subdivide_d = 0);
	static void create_quad(Ref<Mesh> mesh, Size2 size = Size2(1.0, 1.0), Vector3 center_offset = Vector3(0.0, 0.0, 0.0));
	static void create_quad_with_indices(Ref<Mesh> mesh, Size2 size = Size2(1.0, 1.0), Vector3 center_offset = Vector3(0.0, 0.0, 0.0));
	static void create_sphere(Ref<Mesh> mesh, float radius, float height, int radial_segments = 64, int rings = 32, bool is_hemisphere = false);
	static void create_point(Ref<Mesh> mesh);
};

//--STRIP
#endif
//--STRIP
