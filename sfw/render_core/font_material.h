#ifndef FONT_MATERIAL_H
#define FONT_MATERIAL_H

#include "render_core/material.h"
#include "render_core/texture.h"

#include "render_core/render_state.h"

class FontMaterial : public Material {
public:
	int get_material_id() {
		return 11;
	}

	void bind_uniforms() {
		set_uniform(projection_matrix_location, RenderState::projection_matrix_2d);
		set_uniform(model_view_matrix_location, RenderState::model_view_matrix_2d);

		if (texture) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->get_gl_texture());
			glUniform1i(texture_location, 0);
		}
	}

	void setup_uniforms() {
		projection_matrix_location = get_uniform("u_proj_matrix");
		model_view_matrix_location = get_uniform("u_model_view_matrix");

		texture_location = get_uniform("u_texture");
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
			"attribute vec2 a_uv;\n"
			"\n"
			"varying vec2 v_uv;\n"
			"\n"
			"void main() {\n"
			"  v_uv = a_uv;\n"
			"  gl_Position = u_proj_matrix * u_model_view_matrix * a_position;\n"
			"}"
		};

		return vertex_shader_source;
	}

	const GLchar **get_fragment_shader_source() {
		static const GLchar *fragment_shader_source[] = {
			"precision mediump float;\n"
			"\n"
			"uniform sampler2D u_texture;\n"
			"\n"
			"varying vec2 v_uv;\n"
			"\n"
			"void main() {\n"
			"  vec4 col = texture2D(u_texture, v_uv);\n"
			"\n"
			"  if (col.r < 0.5) {\n"
			"    discard;\n"
			"  }\n"
			"\n"
			"  gl_FragColor = col;\n"
			"}"
		};

		return fragment_shader_source;
	}

	FontMaterial() {
		projection_matrix_location = 0;
		model_view_matrix_location = 0;

		texture_location = 0;
		texture = NULL;
	}

	GLint projection_matrix_location;
	GLint model_view_matrix_location;

	GLint texture_location;

	Texture *texture;
};

#endif // TEXT_MATERIAL_H
