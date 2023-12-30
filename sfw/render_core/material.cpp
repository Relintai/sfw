#include "material.h"

#include <stdio.h>

void Material::bind() {
    //csak main thread!

    if (!shader) {
        shader = ShaderCache::get_singleton()->get_shader(get_material_id());

        if (!shader) {
            shader = memnew(Shader());

            shader->set_vertex_shader_source(get_vertex_shader_source());
            shader->set_fragment_shader_source(get_fragment_shader_source());

            shader->compile();

            ShaderCache::get_singleton()->add_shader(get_material_id(), shader);
        }

        setup_uniforms();
    }

    if (current_material && current_material != this) {
        current_material->unbind();

        setup_state();
    }

    current_material = this;

    shader->bind();

    bind_uniforms();
}

void Material::unbind() {
}
void Material::bind_uniforms() {
}
void Material::setup_uniforms() {
}
void Material::setup_state() {
}

GLint Material::get_uniform(const char* name) {
    GLint uniform = glGetUniformLocation(shader->program, name);

    if (uniform == -1) {
        printf("%s is not a valid glsl program variable!\n", name);
    }

    return uniform;
}

Material::Material() {
    shader = NULL;
}
Material::~Material() {
}

Material *Material::current_material = NULL;
