#ifndef COLOR_MATERIAL_H
#define COLOR_MATERIAL_H

#include "material.h"

#include "camera.h"

class ColorMaterial : public Material {
public:
	int get_material_id() {
		return 2;
	}

	void bind_uniforms() {
		set_uniform(projection_matrix_location, Camera::current_camera->projection_matrix);
		set_uniform(camera_matrix_location, Camera::current_camera->camera_transform);
		set_uniform(model_view_matrix_location, Camera::current_camera->model_view_matrix);
	}

	void setup_uniforms() {
		projection_matrix_location = get_uniform("u_proj_matrix");
        camera_matrix_location = get_uniform("u_camera_matrix");
		model_view_matrix_location = get_uniform("u_model_view_matrix");
	}

	const GLchar **get_vertex_shader_source() {
		static const GLchar *vertex_shader_source[] = {
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

		return vertex_shader_source;
	}

	const GLchar **get_fragment_shader_source() {
		static const GLchar *fragment_shader_source[] = {
			"precision mediump float;"
			"varying vec4 v_color;\n"
			"\n"
			"void main() { gl_FragColor = v_color; }\n"
		};

		return fragment_shader_source;
	}

	ColorMaterial() {
		projection_matrix_location = 0;
		camera_matrix_location = 0;
		model_view_matrix_location = 0;
	}

	GLint projection_matrix_location;
	GLint camera_matrix_location;
	GLint model_view_matrix_location;
};

#endif