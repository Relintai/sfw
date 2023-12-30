#ifndef SHADER_H
#define SHADER_H

#include "3rd_glad.h"
#include "hash_map.h"

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

	const GLchar **get_vertex_shader_source();
	void set_vertex_shader_source(const GLchar **source);

	const GLchar **get_fragment_shader_source();
	void set_fragment_shader_source(const GLchar **source);

	void print_shader_errors(const GLuint p_program, const char *name);
	void print_program_errors(const GLuint p_program);

	Shader();
	~Shader();

	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	static Shader *current_shader;

protected:
	const GLchar **vertex_shader_source;
	const GLchar **fragment_shader_source;
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
