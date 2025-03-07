
//--STRIP
#include "color_material.h"
#include "render_core/3rd_glad.h"
//--STRIP

void ColorMaterial::bind_uniforms() {
	set_uniform(projection_matrix_location, RenderState::projection_matrix_3d);
	set_uniform(camera_matrix_location, RenderState::camera_transform_3d);
	set_uniform(model_view_matrix_location, RenderState::model_view_matrix_3d);
}

void ColorMaterial::setup_uniforms() {
	projection_matrix_location = get_uniform("u_proj_matrix");
	camera_matrix_location = get_uniform("u_camera_matrix");
	model_view_matrix_location = get_uniform("u_model_view_matrix");
}

String ColorMaterial::get_vertex_shader_source() {
	static const char *vertex_shader_source[] = {
#if defined(__APPLE__)
#else
		"#version 100\n"
		"precision mediump float;\n"
#endif
		"uniform mat4 u_proj_matrix;\n"
		"uniform mat4 u_camera_matrix;\n"
		"uniform mat4 u_model_view_matrix;\n"
		"\n"
		"attribute vec4 a_position;\n"
		"attribute vec4 a_color;\n"
		"\n"
		"varying vec4 v_color;\n"
		"\n"
		"void main() {\n"
		"   v_color = a_color;\n"
		"   gl_Position = u_proj_matrix * u_camera_matrix * u_model_view_matrix * a_position;\n"
		"}\n"
	};

	return String(*vertex_shader_source);
}

String ColorMaterial::get_fragment_shader_source() {
	static const char *fragment_shader_source[] = {
#ifndef __APPLE__
		"#version 100\n"
        "#ifdef GL_ES\n"
        "    precision mediump float;\n"
        "#endif\n"
#endif
		"varying vec4 v_color;\n"
		"\n"
		"void main() { gl_FragColor = v_color; }\n"
	};

	return String(*fragment_shader_source);
}

ColorMaterial::ColorMaterial() {
	projection_matrix_location = 0;
	camera_matrix_location = 0;
	model_view_matrix_location = 0;
}
