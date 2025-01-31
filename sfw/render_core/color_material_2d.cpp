
//--STRIP
#include "color_material_2d.h"
#include "render_core/3rd_glad.h"
//--STRIP

void ColorMaterial2D::bind_uniforms() {
	set_uniform(projection_matrix_location, RenderState::projection_matrix_2d);
	set_uniform(model_view_matrix_location, RenderState::model_view_matrix_2d);
}

void ColorMaterial2D::setup_uniforms() {
	projection_matrix_location = get_uniform("u_proj_matrix");
	model_view_matrix_location = get_uniform("u_model_view_matrix");
}

void ColorMaterial2D::unbind() {
	glDisable(GL_TEXTURE_2D);
}

void ColorMaterial2D::setup_state() {
	glEnable(GL_TEXTURE_2D);
}

String ColorMaterial2D::get_vertex_shader_source() {
	static const char *vertex_shader_source[] = {
#if defined(__APPLE__)
#else
		"#version 100\n"
		"precision mediump float;\n"
#endif
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

	return String(*vertex_shader_source);
}

String ColorMaterial2D::get_fragment_shader_source() {
	static const char *fragment_shader_source[] = {
#ifndef __APPLE__
		"precision mediump float;\n"
		"\n"
#endif
		"varying vec4 v_color;\n"
		"\n"
		"void main() {\n"
		"  gl_FragColor = v_color;\n"
		"}"
	};

	return String(*fragment_shader_source);
}

ColorMaterial2D::ColorMaterial2D() {
	projection_matrix_location = 0;
	model_view_matrix_location = 0;
}
