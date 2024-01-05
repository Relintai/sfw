#ifndef COLOR_MATERIAL_2D_H
#define COLOR_MATERIAL_2D_H

//--STRIP
#include "render_core/material.h"
#include "render_core/texture.h"

#include "render_core/render_state.h"
//--STRIP

class ColorMaterial2D : public Material {
	SFW_OBJECT(ColorMaterial2D, Material);

public:
	int get_material_id() {
		return 1;
	}

	void bind_uniforms();
	void setup_uniforms();
	void unbind();
	void setup_state();

	const GLchar **get_vertex_shader_source();
	const GLchar **get_fragment_shader_source();

	ColorMaterial2D();

	GLint projection_matrix_location;
	GLint model_view_matrix_location;
};

#endif // COLORED_MATERIAL_H
