#ifndef COLORED_MATERIAL_H
#define COLORED_MATERIAL_H

//--STRIP
#include "render_core/material.h"

#include "core/color.h"

#include "render_core/render_state.h"
//--STRIP

class ColoredMaterial : public Material {
public:
	int get_material_id() {
		return 1;
	}

	void bind_uniforms();
	void setup_uniforms();

	const GLchar **get_vertex_shader_source();
	const GLchar **get_fragment_shader_source();

	ColoredMaterial();

	GLint projection_matrix_location;
	GLint model_view_matrix_location;

	GLint tri_color_uniform_location;
	Color color;
};

#endif // COLORED_MATERIAL_H
