//--STRIP
#ifndef TEXTURE_MATERIAL_2D_H
#define TEXTURE_MATERIAL_2D_H
//--STRIP

//--STRIP
#include "render_core/material.h"
#include "render_core/texture.h"

#include "render_core/render_state.h"
//--STRIP

class TextureMaterial2D : public Material {
	SFW_OBJECT(TextureMaterial2D, Material);

public:
	int get_material_id() {
		return 5;
	}

	void bind_uniforms();
	void setup_uniforms();
	void unbind();
	void setup_state();

	const char **get_vertex_shader_source();
	const char **get_fragment_shader_source();

	TextureMaterial2D();
	
	int32_t projection_matrix_location;
	int32_t model_view_matrix_location;

	int32_t texture_location;

	Ref<Texture> texture;
};

//--STRIP
#endif // COLORED_MATERIAL_H
//--STRIP
