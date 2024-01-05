//--STRIP
#include "colored_material.h"
//--STRIP

void ColoredMaterial::bind_uniforms() {
	set_uniform(projection_matrix_location, RenderState::projection_matrix_3d);
	set_uniform(model_view_matrix_location, RenderState::model_view_matrix_3d);

	glUniform4f(tri_color_uniform_location, color.r, color.g, color.b, color.a);
}

void ColoredMaterial::setup_uniforms() {
	projection_matrix_location = get_uniform("u_proj_matrix");
	model_view_matrix_location = get_uniform("u_model_view_matrix");

	tri_color_uniform_location = get_uniform("fragment_color");
}

const GLchar **ColoredMaterial::get_vertex_shader_source() {
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

const GLchar **ColoredMaterial::get_fragment_shader_source() {
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

ColoredMaterial::ColoredMaterial() {
}
