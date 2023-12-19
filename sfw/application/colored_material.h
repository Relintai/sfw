#ifndef COLORED_MATERIAL_H
#define COLORED_MATERIAL_H

#include "material.h"

#include "color.h"

#include "camera.h"

class ColoredMaterial : public Material {
public:
    int get_material_id() {
        return 1;
    }

    void bind_uniforms() {
        //glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(Camera::current_camera->projection_matrix));
        //glUniformMatrix4fv(model_view_matrix_location, 1, GL_FALSE, glm::value_ptr(Camera::current_camera->model_view_matrix));

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

    ColoredMaterial() : Material() {
    }

    GLint projection_matrix_location;
    GLint model_view_matrix_location;

    GLint tri_color_uniform_location;
    Color color;
};



#endif // COLORED_MATERIAL_H
