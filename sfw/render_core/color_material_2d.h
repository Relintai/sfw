#ifndef COLOR_MATERIAL_2D_H
#define COLOR_MATERIAL_2D_H

#include "render_core/material.h"
#include "render_core/texture.h"

#include "render_core/render_state.h"

class ColorMaterial2D : public Material {
	SFW_OBJECT(ColorMaterial2D, Material);

public:
	int get_material_id() {
		return 17;
	}

	void bind_uniforms() {
		set_uniform(projection_matrix_location, RenderState::projection_matrix_2d);
		set_uniform(model_view_matrix_location, RenderState::model_view_matrix_2d);
	}

	void setup_uniforms() {
		projection_matrix_location = get_uniform("u_proj_matrix");
		model_view_matrix_location = get_uniform("u_model_view_matrix");
	}

	void unbind() {
		glDisable(GL_TEXTURE_2D);
	}

	void setup_state() {
		glEnable(GL_TEXTURE_2D);
	}

	const GLchar **get_vertex_shader_source() {
		static const GLchar *vertex_shader_source[] = {
			"uniform mat4 u_proj_matrix;\n"
			"uniform mat4 u_model_view_matrix;\n"
			"\n"
			"attribute vec4 a_position;\n"
			"attribute vec4 a_color;\n"
			"\n"
			"varying vec4 v_color;\n"
			"\n"
			"void main() {\n"
			"  v_color = a_color;\n"
			"  gl_Position = u_proj_matrix * u_model_view_matrix * a_position;\n"
			"}"
		};

		return vertex_shader_source;
	}

	const GLchar **get_fragment_shader_source() {
		static const GLchar *fragment_shader_source[] = {
			"precision mediump float;\n"
			"\n"
			"varying vec4 v_color;\n"
			"\n"
			"void main() {\n"
			"  gl_FragColor = v_color;\n"
			"}"
		};

		return fragment_shader_source;
	}

	ColorMaterial2D() {
		projection_matrix_location = 0;
		model_view_matrix_location = 0;
	}

	GLint projection_matrix_location;
	GLint model_view_matrix_location;
};

#endif // COLORED_MATERIAL_H
