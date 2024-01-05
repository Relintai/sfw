#ifndef SHADER_H
#define SHADER_H

//--STRIP
#include "render_core/3rd_glad.h"
#include "core/hash_map.h"
//--STRIP

class Shader {
public:
	enum VertexAttributes {
		ATTRIBUTE_POSITION = 0,
		ATTRIBUTE_NORMAL,
		ATTRIBUTE_COLOR,
		ATTRIBUTE_UV,
	};

	bool bind();
	void unbind();

	void compile();
	void destroy();

	const char **get_vertex_shader_source();
	void set_vertex_shader_source(const char **source);

	const char **get_fragment_shader_source();
	void set_fragment_shader_source(const char **source);

	void print_shader_errors(const uint32_t p_program, const char *name);
	void print_program_errors(const uint32_t p_program);

	Shader();
	~Shader();

	uint32_t vertex_shader;
	uint32_t fragment_shader;
	uint32_t program;

	static Shader *current_shader;

protected:
	const char **vertex_shader_source;
	const char **fragment_shader_source;
};

class ShaderCache {
public:
	static ShaderCache *get_singleton();

	Shader *get_shader(const int id);
	void add_shader(const int id, Shader *shader);

	ShaderCache();
	~ShaderCache();

protected:
	HashMap<int, Shader *> shaders;
};

#endif // SHADER_H
