#ifndef COLOR_MATERIAL_H
#define COLOR_MATERIAL_H

//--STRIP
#include "render_core/material.h"

#include "render_core/render_state.h"
//--STRIP

class ColorMaterial : public Material {
	SFW_OBJECT(ColorMaterial, Material);

public:
	int get_material_id() {
		return 2;
	}

	void bind_uniforms();
	void setup_uniforms();

	const GLchar **get_vertex_shader_source();
	const GLchar **get_fragment_shader_source();

	ColorMaterial();

	GLint projection_matrix_location;
	GLint camera_matrix_location;
	GLint model_view_matrix_location;
};

#endif