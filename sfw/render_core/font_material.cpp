//--STRIP
#include "font_material.h"
#include "render_core/3rd_glad.h"
//--STRIP

void FontMaterial::bind_uniforms() {
	set_uniform(projection_matrix_location, RenderState::projection_matrix_2d);
	set_uniform(model_view_matrix_location, RenderState::model_view_matrix_2d);

	if (texture.is_valid()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->get_gl_texture());
		glUniform1i(texture_location, 0);
	}
}

void FontMaterial::setup_uniforms() {
	projection_matrix_location = get_uniform("u_proj_matrix");
	model_view_matrix_location = get_uniform("u_model_view_matrix");

	texture_location = get_uniform("u_texture");
}

void FontMaterial::unbind() {
	glDisable(GL_TEXTURE_2D);
}

void FontMaterial::setup_state() {
	glEnable(GL_TEXTURE_2D);
}

String FontMaterial::get_vertex_shader_source() {
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
		"attribute vec2 a_uv;\n"
		"attribute vec4 a_color;\n"
		"\n"
		"varying vec2 v_uv;\n"
		"varying vec4 v_color;\n"
		"\n"
		"void main() {\n"
		"  v_uv = a_uv;\n"
		"  v_color = a_color;\n"
		"  gl_Position = u_proj_matrix * u_model_view_matrix * a_position;\n"
		"}"
	};

	return String(*vertex_shader_source);
}

String FontMaterial::get_fragment_shader_source() {
	static const char *fragment_shader_source[] = {
#ifndef __APPLE__
		"#version 100\n"
        "#ifdef GL_ES\n"
        "    precision mediump float;\n"
        "#endif\n"
#endif
		"\n"
		"uniform sampler2D u_texture;\n"
		"\n"
		"varying vec2 v_uv;\n"
		"varying vec4 v_color;\n"
		"\n"
		"void main() {\n"
		"  vec4 col = texture2D(u_texture, v_uv);\n"
		"\n"
		"  if (col.r < 0.5) {\n"
		"    discard;\n"
		"  }\n"
		"\n"
		"  gl_FragColor = col * v_color;\n"
		"}"
	};

	return String(*fragment_shader_source);
}

FontMaterial::FontMaterial() {
	projection_matrix_location = 0;
	model_view_matrix_location = 0;

	texture_location = 0;
}
