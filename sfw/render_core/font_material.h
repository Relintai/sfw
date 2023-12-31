#ifndef FONT_MATERIAL_H
#define FONT_MATERIAL_H

//--STRIP
#include "render_core/material.h"
#include "render_core/texture.h"

#include "render_core/render_state.h"
//--STRIP

class FontMaterial : public Material {
	SFW_OBJECT(FontMaterial, Material);

public:
	int get_material_id() {
		return 4;
	}

	void bind_uniforms();
	void setup_uniforms();
	void unbind();
	void setup_state();

	const char **get_vertex_shader_source();
	const char **get_fragment_shader_source();

	FontMaterial();

	int32_t projection_matrix_location;
	int32_t model_view_matrix_location;

	int32_t texture_location;

	Ref<Texture> texture;
};

#endif // TEXT_MATERIAL_H
