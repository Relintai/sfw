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

	void bind_uniforms() {
		set_uniform(projection_matrix_location, RenderState::projection_matrix_3d);
		set_uniform(model_view_matrix_location, RenderState::model_view_matrix_3d);

		glUniform4f(tri_color_uniform_location, color.r, color.g, color.b, color.a);
	}

	void setup_uniforms() {
		projection_matrix_location = get_uniform("u_proj_matrix");
		model_view_matrix_location = get_uniform("u_model_view_matrix");

		tri_color_uniform_location = get_uniform("fragment_color");
	}

	const GLchar **get_vertex_shader_source() {
		static const GLchar *vertex_shader_source[] = {
			"uniform mat4 u_proj_matrix;\n"
			"uniform mat4 u_model_view_matrix;\n"
			"\n"
			"attribute vec4 a_position;\n"
			"\n"
			"void main() {\n"
			"  gl_Position = u_proj_matrix * u_model_view_matrix * a_position;\n"
			"}"
		};

		return vertex_shader_source;
	}

	const GLchar **get_fragment_shader_source() {
		static const GLchar *fragment_shader_source[] = {
			"precision mediump float;\n"
			"\n"
			"uniform vec4 fragment_color;\n"
			"\n"
			"void main() {\n"
			"  gl_FragColor = fragment_color;\n"
			"}"
		};

		return fragment_shader_source;
	}

	ColoredMaterial() :
			Material() {
	}

	GLint projection_matrix_location;
	GLint model_view_matrix_location;

	GLint tri_color_uniform_location;
	Color color;
};

#endif // COLORED_MATERIAL_H
