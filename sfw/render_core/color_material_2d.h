//--STRIP
#ifndef COLOR_MATERIAL_2D_H
#define COLOR_MATERIAL_2D_H
//--STRIP

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

	const char **get_vertex_shader_source();
	const char **get_fragment_shader_source();

	ColorMaterial2D();

	int32_t projection_matrix_location;
	int32_t model_view_matrix_location;
};
//--STRIP
#endif // COLORED_MATERIAL_H
//--STRIP
