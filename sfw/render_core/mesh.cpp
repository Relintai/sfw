//--STRIP
#include "render_core/mesh.h"

#include "render_core/shader.h"
//--STRIP

void Mesh::add_vertex2(float x, float y) {
	vertices.push_back(x);
	vertices.push_back(y);
}
void Mesh::add_vertex3(float x, float y, float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Mesh::add_normal(float x, float y, float z) {
	normals.push_back(x);
	normals.push_back(y);
	normals.push_back(z);
}
void Mesh::add_color(float r, float g, float b, float a) {
	colors.push_back(r);
	colors.push_back(g);
	colors.push_back(b);
	colors.push_back(a);
}
void Mesh::add_color(const Color &p_color) {
	colors.push_back(p_color.r);
	colors.push_back(p_color.g);
	colors.push_back(p_color.b);
	colors.push_back(p_color.a);
}

void Mesh::add_uv(float u, float v) {
	uvs.push_back(u);
	uvs.push_back(v);
}

void Mesh::add_index(uint32_t index) {
	indices.push_back(index);
}
void Mesh::add_triangle(uint32_t i1, uint32_t i2, uint32_t i3) {
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

void Mesh::flip_faces() {
	if (normals.size() > 0 && indices.size() > 0) {
		{
			int nc = normals.size();
			float *w = normals.ptrw();
			for (int i = 0; i < nc; i++) {
				w[i] = -w[i];
			}
		}

		{
			int ic = indices.size();
			uint32_t *w = indices.ptrw();
			for (int i = 0; i < ic; i += 3) {
				SWAP(w[i + 0], w[i + 1]);
			}
		}
	}
}

void Mesh::update_aabb() {
	aabb = AABB();

	if (vertex_dimesions == 2) {
		int size = vertices.size();

		if (size < 2) {
			return;
		}

		const float *v = vertices.ptr();

		aabb.position.x = v[0];
		aabb.position.y = v[1];

		Vector3 vert;

		for (int i = 0; i < size; i += 2) {
			vert.x = v[i];
			vert.y = v[i + 1];

			aabb.expand_to(vert);
		}
	} else if (vertex_dimesions == 3) {
		int size = vertices.size();

		if (size < 3) {
			return;
		}

		const float *v = vertices.ptr();

		aabb.position.x = v[0];
		aabb.position.y = v[1];
		aabb.position.z = v[2];

		Vector3 vert;

		for (int i = 0; i < size; i += 2) {
			vert.x = v[i];
			vert.y = v[i + 1];
			vert.z = v[i + 2];

			aabb.expand_to(vert);
		}
	}
}

void Mesh::clear() {
	vertices.clear();
	normals.clear();
	colors.clear();
	uvs.clear();
	indices.clear();
}

void Mesh::upload() {
	if (vertices.size() == 0) {
		return;
	}

	if (!VBO) {
		glGenBuffers(1, &VBO);
	}

	vertices_vbo_size = sizeof(float) * vertices.size();
	normals_vbo_size = sizeof(float) * normals.size();
	colors_vbo_size = sizeof(float) * colors.size();
	uvs_vbo_size = sizeof(float) * uvs.size();
	indices_vbo_size = sizeof(float) * indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_vbo_size + normals_vbo_size + colors_vbo_size + uvs_vbo_size, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_vbo_size, vertices.ptr());

	if (normals_vbo_size > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, vertices_vbo_size, normals_vbo_size, normals.ptr());
	}

	if (colors_vbo_size > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, vertices_vbo_size + normals_vbo_size, colors_vbo_size, colors.ptr());
	}

	if (uvs_vbo_size > 0) {
		glBufferSubData(GL_ARRAY_BUFFER, vertices_vbo_size + normals_vbo_size + colors_vbo_size, uvs_vbo_size, uvs.ptr());
	}

	if (indices_vbo_size > 0) {
		if (!IBO) {
			glGenBuffers(1, &IBO);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_size, indices.ptr(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::destroy() {
	if (VBO) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (IBO) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
}
void Mesh::render() {
	if (vertices.size() == 0) {
		return;
	}

	if (!Shader::current_shader) {
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(Shader::ATTRIBUTE_POSITION, vertex_dimesions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::ATTRIBUTE_POSITION);

	if (normals_vbo_size > 0) {
		glVertexAttribPointer(Shader::ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void *)(uintptr_t)(vertices_vbo_size));
		glEnableVertexAttribArray(Shader::ATTRIBUTE_NORMAL);
	}

	if (colors_vbo_size > 0) {
		glVertexAttribPointer(Shader::ATTRIBUTE_COLOR, 4, GL_FLOAT, GL_FALSE, 0, (void *)(uintptr_t)(vertices_vbo_size + normals_vbo_size));
		glEnableVertexAttribArray(Shader::ATTRIBUTE_COLOR);
	}

	if (uvs_vbo_size > 0) {
		glVertexAttribPointer(Shader::ATTRIBUTE_UV, 2, GL_FLOAT, GL_FALSE, 0, (void *)(uintptr_t)(vertices_vbo_size + normals_vbo_size + colors_vbo_size));
		glEnableVertexAttribArray(Shader::ATTRIBUTE_UV);
	}

	if (indices_vbo_size > 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid *)0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}

	glDisableVertexAttribArray(Shader::ATTRIBUTE_POSITION);

	if (normals_vbo_size > 0) {
		glDisableVertexAttribArray(Shader::ATTRIBUTE_NORMAL);
	}

	if (colors_vbo_size > 0) {
		glDisableVertexAttribArray(Shader::ATTRIBUTE_COLOR);
	}

	if (uvs_vbo_size > 0) {
		glDisableVertexAttribArray(Shader::ATTRIBUTE_UV);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh() {
	VBO = 0;
	IBO = 0;

	vertex_dimesions = 3;

	vertices_vbo_size = 0;
	normals_vbo_size = 0;
	colors_vbo_size = 0;
	uvs_vbo_size = 0;
	indices_vbo_size = 0;
}
Mesh::Mesh(int vert_dim) {
	VBO = 0;
	IBO = 0;

	vertex_dimesions = vert_dim;

	vertices_vbo_size = 0;
	normals_vbo_size = 0;
	colors_vbo_size = 0;
	uvs_vbo_size = 0;
	indices_vbo_size = 0;
}
Mesh::~Mesh() {
	destroy();
	clear();
}
