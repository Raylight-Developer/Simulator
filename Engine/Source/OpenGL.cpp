#include "OpenGL.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

CORE::Confirm<GLuint> OpenGL::compileFragShader(const string& vert_file_path, const string& frag_file_path) {
	GLuint vert_shader = GL->glCreateShader(GL_VERTEX_SHADER);
	const string vertex_code = loadFromFile(vert_file_path);
	const char* vertex_code_cstr = vertex_code.c_str();
	GL->glShaderSource(vert_shader, 1, &vertex_code_cstr, NULL);
	GL->glCompileShader(vert_shader);

	if (!checkShaderCompilation(vert_shader, vertex_code)) {
		return CORE::Confirm<GLuint>();
	}

	GLuint frag_shader = GL->glCreateShader(GL_FRAGMENT_SHADER);
	const string fragment_code = loadFromFile(frag_file_path);
	const char* fragment_code_cstr = fragment_code.c_str();
	GL->glShaderSource(frag_shader, 1, &fragment_code_cstr, NULL);
	GL->glCompileShader(frag_shader);

	if (!checkShaderCompilation(frag_shader, fragment_code)) {
		return CORE::Confirm<GLuint>();
	}

	GLuint shader_program =GL-> glCreateProgram();
	GL->glAttachShader(shader_program, vert_shader);
	GL->glAttachShader(shader_program, frag_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(vert_shader);
	GL->glDeleteShader(frag_shader);

	return CORE::Confirm(shader_program);
}

CORE::Confirm<GLuint> OpenGL::compileFragShaderFromStr(const string& vert_file_path, const string& fragment_code) {
	GLuint vert_shader = GL->glCreateShader(GL_VERTEX_SHADER);
	const string vertex_code = loadFromFile(vert_file_path);
	const char* vertex_code_cstr = vertex_code.c_str();
	GL->glShaderSource(vert_shader, 1, &vertex_code_cstr, NULL);
	GL->glCompileShader(vert_shader);

	if (!checkShaderCompilation(vert_shader, vertex_code)) {
		return CORE::Confirm<GLuint>();
	}

	GLuint frag_shader = GL->glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragment_code_cstr = fragment_code.c_str();
	GL->glShaderSource(frag_shader, 1, &fragment_code_cstr, NULL);
	GL->glCompileShader(frag_shader);

	if (!checkShaderCompilation(frag_shader, fragment_code)) {
		return CORE::Confirm<GLuint>();
	}

	GLuint shader_program =GL-> glCreateProgram();
	GL->glAttachShader(shader_program, vert_shader);
	GL->glAttachShader(shader_program, frag_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(vert_shader);
	GL->glDeleteShader(frag_shader);

	return CORE::Confirm(shader_program);
}

CORE::Confirm<GLuint> OpenGL::compileCompShader(const string& comp_file_path) {
	string compute_code = preprocessShader(comp_file_path);

	const char* compute_code_cstr = compute_code.c_str();
	GLuint comp_shader = GL->glCreateShader(GL_COMPUTE_SHADER);
	GL->glShaderSource(comp_shader, 1, &compute_code_cstr, NULL);
	GL->glCompileShader(comp_shader);

	if (!checkShaderCompilation(comp_shader, compute_code)) {
		return CORE::Confirm<GLuint>();
	}

	GLuint shader_program = GL->glCreateProgram();
	GL->glAttachShader(shader_program, comp_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(comp_shader);

	return CORE::Confirm(shader_program);
}

bool OpenGL::recompileFragShader(GLuint& handle, const string& vert_file_path, const string& frag_file_path) {
	auto confirm = compileFragShader(vert_file_path, frag_file_path);
	if (confirm) {
		GL->glDeleteProgram(handle);
		handle = confirm.data;
		return true;
	}
	return false;
}

bool OpenGL::recompileCompShader(GLuint& handle, const string& comp_file_path) {
	auto confirm = compileCompShader(comp_file_path);
	if (confirm) {
		GL->glDeleteProgram(handle);
		handle = confirm.data;
		return true;
	}
	return false;
}

bool OpenGL::checkShaderCompilation(const GLuint& shader, const string& shader_code) {
	GLint success;
	GL->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		GL->glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		LOGL(NL NL << ERROR << "[OpenGL] Shader Compilation Failed: ");
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
		LOGL(NL NL << ERROR << "[OpenGL] Program Linking Failed: " << infoLog);
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

	U64 lineNumber = stoU64(error_str.substr(pos + 1, endPos - pos - 1));

	Tokens lines = f_split(shader_code, "\n");

	U64 startLine = max(0ULL, lineNumber - 4);
	U64 endLine = min(lines.size(), lineNumber + 3);

	for (U64 i = startLine; i < endLine; ++i) {
		LOG NL << (i + 1) << ": " << lines[i];
		if (i == lineNumber - 1) {
			LOG NL << ANSI_RED << "^^^^^^-- Error here: " ANSI_RESET << error_str;
		}
	}
	LOG -= 1;
	LOG NL NL;
	FLUSH;
}

OpenGL::Texture::Texture() :
	handle(0),
	resolution(T_V2<U32>(0,0)),
	internalFormat(GL_RGBA8),
	format(GL_RGBA),
	type(GL_UNSIGNED_BYTE)
{}

void OpenGL::Texture::init(const T_V2<U32>& resolution, GLenum format, GLenum type) {
	this->resolution = resolution;
	this->format = format;
	this->type = type;

	this->internalFormat = chooseInternalFormat(format, type);

	GL->glGenTextures(1, &handle);
	GL->glBindTexture(GL_TEXTURE_2D, handle);
	GL->glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolution.x, resolution.y, 0, format, type, nullptr);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL->glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::Texture::resize(const T_V2<U32>& resolution) {
	this->resolution = resolution;

	GL->glDeleteTextures(1, &handle);

	GL->glBindTexture(GL_TEXTURE_2D, handle);
	GL->glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolution.x, resolution.y, 0, format, type, nullptr);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL->glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::Texture::setPixels(const T_V2<U32>& resolution, const void* data) {
	GL->glTextureSubImage2D(handle, 0, 0, 0, resolution.x, resolution.y, format, type, data);
}

GLenum OpenGL::Texture::chooseInternalFormat(const GLenum& format, const GLenum& type) {
	using Entry = std::tuple<GLenum, GLenum, GLenum>;

	static constexpr std::array<Entry, 9> formatTable = { {
		{ GL_RGBA, GL_FLOAT,         GL_RGBA32F },
		{ GL_RGBA, GL_HALF_FLOAT,    GL_RGBA16F },
		{ GL_RGBA, GL_UNSIGNED_BYTE, GL_RGBA8 },

		{ GL_RGB,  GL_FLOAT,         GL_RGB32F },
		{ GL_RGB,  GL_HALF_FLOAT,    GL_RGB16F },
		{ GL_RGB,  GL_UNSIGNED_BYTE, GL_RGB8 },

		{ GL_RED,  GL_FLOAT,         GL_R32F },
		{ GL_RED,  GL_HALF_FLOAT,    GL_R16F },
		{ GL_RED,  GL_UNSIGNED_BYTE, GL_R8 },
		} };

	for (const auto& [fmt, typ, internalFmt] : formatTable) {
		if (fmt == format && typ == type) {
			return internalFmt;
		}
	}

	throw std::runtime_error("Unsupported OpenGL Texture format+type combination.");
}

OpenGL::Framebuffer::Framebuffer() :
	handle(0)
{}

void OpenGL::Framebuffer::init(const T_V2<U32>& resolution) {
	GL->glGenFramebuffers(1, &handle);
	GL->glBindFramebuffer(GL_FRAMEBUFFER, handle);

	texture.init(resolution);

	GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.handle, 0);
	GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::Framebuffer::resize(const T_V2<U32>& resolution) {
	GL->glBindFramebuffer(GL_FRAMEBUFFER, handle);

	texture.resize(resolution);

	GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.handle, 0);
	GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::Framebuffer::renderToSwapchain() const {
	GL->glBindFramebuffer(GL_READ_FRAMEBUFFER, handle);
	GL->glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	GL->glBlitFramebuffer(0, 0, texture.resolution.x, texture.resolution.y, 0, 0, texture.resolution.x, texture.resolution.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}