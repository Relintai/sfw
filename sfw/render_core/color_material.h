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

	const char **get_vertex_shader_source();
	const char **get_fragment_shader_source();

	ColorMaterial();

	int32_t projection_matrix_location;
	int32_t camera_matrix_location;
	int32_t model_view_matrix_location;
};

#endif
