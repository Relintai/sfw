#ifndef MESH_H
#define MESH_H

//--STRIP
#include "core/vector.h"
#include "core/int_types.h"
#include "core/color.h"

#include "object/resource.h"

#include "render_core/3rd_glad.h"
//--STRIP

class Mesh : public Resource {
	SFW_OBJECT(Mesh, Resource);

public:
	void add_vertex2(float x, float y);
	void add_vertex3(float x, float y, float z);

	void add_normal(float x, float y, float z);
	void add_color(float r = 1, float g = 1, float b = 1, float a = 1);
    void add_color(const Color &p_color);

	void add_uv(float u, float v);

	void add_index(uint32_t index);
	void add_triangle(uint32_t i1, uint32_t i2, uint32_t i3);

	void clear();

	void upload();
	void destroy();
	void render();

	Mesh();
	Mesh(int vert_dim);
	virtual ~Mesh();

	GLuint VBO;
	GLuint IBO;

	int vertex_dimesions;

	Vector<float> vertices;
	Vector<float> normals;
	Vector<float> colors;
	Vector<float> uvs;
	Vector<uint32_t> indices;

protected:
	uint32_t vertices_vbo_size;
	uint32_t normals_vbo_size;
	uint32_t colors_vbo_size;
	uint32_t uvs_vbo_size;
	uint32_t indices_vbo_size;
};

#endif // MESH_H
