//--STRIP
#include "render_core/shader.h"

#include <stdio.h>

#include "render_core/3rd_glad.h"
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
	ERR_FAIL_COND(_vertex_shader_source.empty());
	ERR_FAIL_COND(_fragment_shader_source.empty());

	if (!program) {
		program = glCreateProgram();
	}

	if (!vertex_shader) {
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	}

	if (!fragment_shader) {
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	CharString vertex_shader_source = _vertex_shader_source.utf8();
	const char *vss = vertex_shader_source.get_data();

	glShaderSource(vertex_shader, 1, &vss, NULL);
	glCompileShader(vertex_shader);

	int32_t shader_compiled = GL_FALSE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE) {
		print_shader_errors(vertex_shader, "compiling Vertex Shader");
		return;
	}

	glAttachShader(program, vertex_shader);

	CharString fragment_shader_source = _fragment_shader_source.utf8();
	const char *fss = fragment_shader_source.get_data();

	glShaderSource(fragment_shader, 1, &fss, NULL);
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

String Shader::get_vertex_shader_source() {
	return _vertex_shader_source;
}
void Shader::set_vertex_shader_source(const String &source) {
	_vertex_shader_source = source;
}

String Shader::get_fragment_shader_source() {
	return _fragment_shader_source;
}
void Shader::set_fragment_shader_source(const String &source) {
	_fragment_shader_source = source;
}

void Shader::print_shader_errors(const uint32_t p_program, const String &name) {
	int max_length = 5000;
	char error_log[5000];

	glGetShaderInfoLog(p_program, max_length, &max_length, error_log);

	ERR_PRINT("Error " + name + "\n" + String::utf8(error_log, max_length));
}

void Shader::print_program_errors(const uint32_t p_program) {
	if (glIsProgram(program)) {
		int info_length = 0;
		int max_length = 5000;
		char info_log[5000];

		glGetProgramiv(p_program, GL_INFO_LOG_LENGTH, &info_length);

		glGetProgramInfoLog(p_program, max_length, &info_length, info_log);

		if (info_length > 0) {
			ERR_PRINT(String::utf8(info_log, info_length));
		}
	} else {
		ERR_PRINT("print_program_errors: Not a program!\n");
	}
}

Shader::Shader() {
	vertex_shader = 0;
	fragment_shader = 0;
	program = 0;
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
