//--STRIP
#include "render_core/shader.h"

#include <stdio.h>
//--STRIP

bool Shader::bind() {
	if (current_shader != this) {
		glUseProgram(program);

		current_shader = this;

		return true;
	}

	return false;
}

void Shader::unbind() {
	if (current_shader == this) {
		glUseProgram(0);

		current_shader = NULL;
	}
}

void Shader::compile() {
	if (!program) {
		program = glCreateProgram();
	}

	if (!vertex_shader) {
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	}

	if (!fragment_shader) {
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	const char **vertex_shader_source = get_vertex_shader_source();

	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	int32_t shader_compiled = GL_FALSE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE) {
		print_shader_errors(vertex_shader, "compiling Vertex Shader");
		return;
	}

	glAttachShader(program, vertex_shader);

	const char **fragment_shader_source = get_fragment_shader_source();

	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	shader_compiled = GL_FALSE;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE) {
		print_shader_errors(fragment_shader, "compiling Fragment Shader");
		return;
	}

	glAttachShader(program, fragment_shader);

	glBindAttribLocation(program, ATTRIBUTE_POSITION, "a_position");
	glBindAttribLocation(program, ATTRIBUTE_NORMAL, "a_normal");
	glBindAttribLocation(program, ATTRIBUTE_COLOR, "a_color");
	glBindAttribLocation(program, ATTRIBUTE_UV, "a_uv");

	glLinkProgram(program);

	int32_t program_compiled = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &program_compiled);
	if (program_compiled != GL_TRUE) {
		print_program_errors(program);
		return;
	}
}
void Shader::destroy() {
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteProgram(program);
}

const char **Shader::get_vertex_shader_source() {
	return vertex_shader_source;
}
void Shader::set_vertex_shader_source(const char **source) {
	vertex_shader_source = source;
}

const char **Shader::get_fragment_shader_source() {
	return fragment_shader_source;
}
void Shader::set_fragment_shader_source(const char **source) {
	fragment_shader_source = source;
}

void Shader::print_shader_errors(const uint32_t p_program, const char *name) {
	int max_length = 5000;
	Vector<char> error_log;
	error_log.resize(max_length);

	glGetShaderInfoLog(p_program, max_length, &max_length, error_log.ptrw());

	printf("Error %s!\n", name);
	printf("%s!\n", error_log.ptr());
}

void Shader::print_program_errors(const uint32_t p_program) {
	if (glIsProgram(program)) {
		int info_length = 0;
		int max_length = 5000;

		glGetProgramiv(p_program, GL_INFO_LOG_LENGTH, &info_length);

		char *info_log = new char[max_length];

		glGetProgramInfoLog(p_program, max_length, &info_length, info_log);

		if (info_length > 0) {
			printf("%s\n", info_log);
		}

		delete[] info_log;
	} else {
		printf("print_program_errors: Not a program!\n");
	}
}

Shader::Shader() {
	vertex_shader = 0;
	fragment_shader = 0;
	program = 0;

	vertex_shader_source = NULL;
	fragment_shader_source = NULL;
}
Shader::~Shader() {
	destroy();
}

Shader *Shader::current_shader = NULL;

//Meyers singleton
//thread safe
ShaderCache *ShaderCache::get_singleton() {
	static ShaderCache instance;

	return &instance;
}

Shader *ShaderCache::get_shader(const int id) {
	return shaders[id];
}
void ShaderCache::add_shader(const int id, Shader *shader) {
	shaders[id] = shader;
}

ShaderCache::ShaderCache() {
}
ShaderCache::~ShaderCache() {
	for (HashMap<int, Shader *>::Element *E = shaders.front(); E; E = E->next) {
		memdelete(E->get());
	}

	shaders.clear();
}
