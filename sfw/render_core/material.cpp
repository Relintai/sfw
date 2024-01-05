//--STRIP
#include "render_core/material.h"

#include <stdio.h>
//--STRIP

void Material::bind() {
	//csak main thread!

	if (!shader) {
		shader = ShaderCache::get_singleton()->get_shader(get_material_id());

		if (!shader) {
			shader = memnew(Shader());

			shader->set_vertex_shader_source(get_vertex_shader_source());
			shader->set_fragment_shader_source(get_fragment_shader_source());

			shader->compile();

			ShaderCache::get_singleton()->add_shader(get_material_id(), shader);
		}

		setup_uniforms();
	}

	if (current_material && current_material != this) {
		current_material->unbind();

		setup_state();
	}

	current_material = this;

	shader->bind();

	bind_uniforms();
}

void Material::unbind() {
}
void Material::bind_uniforms() {
}
void Material::setup_uniforms() {
}
void Material::setup_state() {
}

int32_t Material::get_uniform(const char *name) {
	int32_t uniform = glGetUniformLocation(shader->program, name);

	if (uniform == -1) {
		printf("%s is not a valid glsl program variable!\n", name);
	}

	return uniform;
}

Material::Material() {
	shader = NULL;
}
Material::~Material() {
}

void Material::set_uniform(int32_t p_uniform, const Transform &p_transform) {
	const Transform &tr = p_transform;

	GLfloat matrix[16] = { /* build a 16x16 matrix */
		tr.basis.rows[0][0],
		tr.basis.rows[1][0],
		tr.basis.rows[2][0],
		0,
		tr.basis.rows[0][1],
		tr.basis.rows[1][1],
		tr.basis.rows[2][1],
		0,
		tr.basis.rows[0][2],
		tr.basis.rows[1][2],
		tr.basis.rows[2][2],
		0,
		tr.origin.x,
		tr.origin.y,
		tr.origin.z,
		1
	};

	glUniformMatrix4fv(p_uniform, 1, false, matrix);
}

void Material::set_uniform(int32_t p_uniform, const Transform2D &p_transform) {
	const Transform2D &tr = p_transform;

	GLfloat matrix[16] = { /* build a 16x16 matrix */
		tr.columns[0][0],
		tr.columns[0][1],
		0,
		0,
		tr.columns[1][0],
		tr.columns[1][1],
		0,
		0,
		0,
		0,
		1,
		0,
		tr.columns[2][0],
		tr.columns[2][1],
		0,
		1
	};

	glUniformMatrix4fv(p_uniform, 1, false, matrix);
}

void Material::set_uniform(int32_t p_uniform, const Projection &p_matrix) {
	GLfloat matrix[16];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i * 4 + j] = p_matrix.matrix[i][j];
		}
	}

	glUniformMatrix4fv(p_uniform, 1, false, matrix);
}

Material *Material::current_material = NULL;
