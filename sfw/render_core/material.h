//--STRIP
#ifndef MATERIAL_H
#define MATERIAL_H
//--STRIP

//--STRIP
#include "core/projection.h"
#include "core/transform.h"
#include "core/transform_2d.h"
#include "object/reference.h"
#include "render_core/shader.h"
//--STRIP

class Material : public Reference {
	SFW_OBJECT(Material, Reference);

public:
	void bind();

	virtual void unbind();
	virtual int get_material_id() = 0;
	virtual void bind_uniforms();
	virtual void setup_uniforms();
	virtual void setup_state();
	virtual const char **get_vertex_shader_source() = 0;
	virtual const char **get_fragment_shader_source() = 0;

	int32_t get_uniform(const char *name);

	Material();
	virtual ~Material();

protected:
	static Material *current_material;

	Shader *shader;

protected:
	void set_uniform(int32_t p_uniform, const Transform &p_transform);
	void set_uniform(int32_t p_uniform, const Transform2D &p_transform);
	void set_uniform(int32_t p_uniform, const Projection &p_matrix);
};

//--STRIP
#endif // MATERIAL_H
//--STRIP
