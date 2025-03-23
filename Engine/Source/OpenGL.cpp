#include "OpenGL.hpp"

KL::Confirm<GLuint> OpenGL::f_compileFragShader(const string& vert_file_path, const string& frag_file_path) {
	GLuint vert_shader = GL->glCreateShader(GL_VERTEX_SHADER);
	const string vertex_code = loadFromFile(vert_file_path);
	const char* vertex_code_cstr = vertex_code.c_str();
	GL->glShaderSource(vert_shader, 1, &vertex_code_cstr, NULL);
	GL->glCompileShader(vert_shader);

	if (!checkShaderCompilation(vert_shader, vertex_code)) {
		return KL::Confirm<GLuint>();
	}

	GLuint frag_shader = GL->glCreateShader(GL_FRAGMENT_SHADER);
	const string fragment_code = loadFromFile(frag_file_path);
	const char* fragment_code_cstr = fragment_code.c_str();
	GL->glShaderSource(frag_shader, 1, &fragment_code_cstr, NULL);
	GL->glCompileShader(frag_shader);

	if (!checkShaderCompilation(frag_shader, fragment_code)) {
		return KL::Confirm<GLuint>();
	}

	GLuint shader_program = GL->glCreateProgram();
	GL->glAttachShader(shader_program, vert_shader);
	GL->glAttachShader(shader_program, frag_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(vert_shader);
	GL->glDeleteShader(frag_shader);

	return KL::Confirm(shader_program);
}

KL::Confirm<GLuint> OpenGL::f_compileCompShader(const string& comp_file_path) {
	string compute_code = preprocessShader(comp_file_path);

	const char* compute_code_cstr = compute_code.c_str();
	GLuint comp_shader = GL->glCreateShader(GL_COMPUTE_SHADER);
	GL->glShaderSource(comp_shader, 1, &compute_code_cstr, NULL);
	GL->glCompileShader(comp_shader);

	if (!checkShaderCompilation(comp_shader, compute_code)) {
		return KL::Confirm<GLuint>();
	}

	GLuint shader_program = GL->glCreateProgram();
	GL->glAttachShader(shader_program, comp_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(comp_shader);

	return KL::Confirm(shader_program);
}

bool OpenGL::checkShaderCompilation(const GLuint& shader, const string& shader_code) {
	GLint success;
	GL->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		GL->glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		PRINT(NL NL << ANSI_RED << "[OpenGL]" ANSI_RESET << " Shader Compilation Failed: ");
		printShaderErrorWithContext(shader_code, infoLog);
		return false;
	}
	return true;
}

bool OpenGL::checkProgramLinking(const GLuint& program) {
	GLint success;
	GL->glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		GL->glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		PRINT(NL NL << ANSI_RED << "[OpenGL]" ANSI_RESET << " Program Linking Failed: " << infoLog);
		return false;
	}
	return true;
}

void OpenGL::printShaderErrorWithContext(const string& shader_code, const string& error_str) {
	LOG += 1;
	size_t pos = error_str.find('(');
	if (pos == string::npos) {
		LOG NL << "Error: Unable to parse error log."; FLUSH;
		LOG -= 1;
		return;
	}

	size_t endPos = error_str.find(')', pos);
	if (endPos == string::npos) {
		LOG NL << "Error: Unable to parse error log."; FLUSH;
		LOG -= 1;
		return;
	}

	uint64 lineNumber = str_to_ul(error_str.substr(pos + 1, endPos - pos - 1));

	Tokens lines = f_split(shader_code, "\n");

	uint64 startLine = max(0ULL, lineNumber - 4);
	uint64 endLine = min(lines.size(), lineNumber + 3);

	for (uint64 i = startLine; i < endLine; ++i) {
		LOG NL << (i + 1) << ": " << lines[i];
		if (i == lineNumber - 1) {
			LOG NL << ANSI_RED << "^-- Error here: " ANSI_RESET << error_str;
		}
	}
	LOG -= 1;
	LOG NL NL;
	FLUSH;
}

GLuint OpenGL::renderLayer(const uvec2& resolution, const GLuint& filter) {
	GLuint ID;
	GL->glCreateTextures(GL_TEXTURE_2D, 1, &ID);
	GL->glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, filter);
	GL->glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, filter);
	GL->glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL->glTextureStorage2D (ID, 1, GL_RGBA32F, resolution.x,resolution.y);
	return ID;
}

void OpenGL::bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name) {
	GL->glUniform1i(GL->glGetUniformLocation(program_id, name.c_str()), unit);
	GL->glBindTextureUnit(unit, id);
}