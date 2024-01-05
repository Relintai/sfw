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
		return 3;
	}

	void bind_uniforms();
	void setup_uniforms();

	const char **get_vertex_shader_source();
	const char **get_fragment_shader_source();

	ColoredMaterial();

	int32_t projection_matrix_location;
	int32_t model_view_matrix_location;

	int32_t tri_color_uniform_location;
	Color color;
};

#endif // COLORED_MATERIAL_H
