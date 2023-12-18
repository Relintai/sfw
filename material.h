#ifndef MATERIAL_H
#define MATERIAL_H

#include "opengl.h"
#include "shader.h"

class Material {
public:
    void bind();

    virtual void unbind();
    virtual int get_material_id() = 0;
    virtual void bind_uniforms();
    virtual void setup_uniforms();
    virtual void setup_state();
    virtual const GLchar **get_vertex_shader_source() = 0;
    virtual const GLchar **get_fragment_shader_source() = 0;

    GLint get_uniform(const char* name);

    Material();
    virtual ~Material();

protected:
    static Material *current_material;

    Shader * shader;
};


#endif // MATERIAL_H
