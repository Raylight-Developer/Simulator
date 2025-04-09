#include "OpenGL.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

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

	U64 lineNumber = stoU64(error_str.substr(pos + 1, endPos - pos - 1));

	Tokens lines = f_split(shader_code, "\n");

	U64 startLine = max(0ULL, lineNumber - 4);
	U64 endLine = min(lines.size(), lineNumber + 3);

	for (U64 i = startLine; i < endLine; ++i) {
		LOG NL << (i + 1) << ": " << lines[i];
		if (i == lineNumber - 1) {
			LOG NL << ANSI_RED << "^-- Error here: " ANSI_RESET << error_str;
		}
	}
	LOG -= 1;
	LOG NL NL;
	FLUSH;
}

GLuint OpenGL::renderLayer(const T_V2<U64>& resolution, const GLuint& filter) {
	GLuint ID;
	GL->glCreateTextures(GL_TEXTURE_2D, 1, &ID);
	GL->glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, filter);
	GL->glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, filter);
	GL->glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL->glTextureStorage2D (ID, 1, GL_RGBA32F, resolution.x, resolution.y);
	return ID;
}

void OpenGL::bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name) {
	GL->glUniform1i(GL->glGetUniformLocation(program_id, name.c_str()), unit);
	GL->glBindTextureUnit(unit, id);
}

void RENDER::Dim_2D::INIT::Line() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Template.vert", "./Shaders/2D/Template.frag");
	if (confirm) {
		SESSION->viewport->gl_data["2D Line Shader"] = confirm.data;
	}

	SESSION->viewport->gl_data["2D Line VAO"] = 0;
	SESSION->viewport->gl_data["2D Line VBO"] = 0;
	SESSION->viewport->gl_data["2D Line EBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["2D Line VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["2D Line VBO"];
	GLuint* EBO = &SESSION->viewport->gl_data["2D Line EBO"];

	const GLfloat vertices[8] = { 0 };
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, VAO);
	GL->glGenBuffers(1, VBO);
	GL->glGenBuffers(1, EBO);

	GL->glBindVertexArray(*VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void RENDER::Dim_2D::INIT::Circle() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Circle.vert", "./Shaders/2D/Circle.frag");
	if (confirm) {
		SESSION->viewport->gl_data["2D Circle Shader"] = confirm.data;
	}

	SESSION->viewport->gl_data["2D Circle VAO"] = 0;
	SESSION->viewport->gl_data["2D Circle VBO"] = 0;
	SESSION->viewport->gl_data["2D Circle EBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["2D Circle VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["2D Circle VBO"];
	GLuint* EBO = &SESSION->viewport->gl_data["2D Circle EBO"];

	const GLfloat vertices[8] = {
		-1, -1,
		-1,  1,
		 1,  1,
		 1, -1
	};
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, VAO);
	GL->glGenBuffers(1, VBO);
	GL->glGenBuffers(1, EBO);

	GL->glBindVertexArray(*VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void RENDER::Dim_2D::Line(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color) {
	F32_V2 lineDir = glm::normalize(v2 - v1);
	F32_V2 perpDir = F32_V2(-lineDir.y, lineDir.x);
	const F32 halfWidth = width * 0.5f;
	F32_V2 n1 = v1 + perpDir * halfWidth;
	F32_V2 n2 = v1 - perpDir * halfWidth;
	F32_V2 n4 = v2 + perpDir * halfWidth;
	F32_V2 n3 = v2 - perpDir * halfWidth;

	const GLfloat vertices[8] = {
		n1.x, n1.y,
		n2.x, n2.y,
		n3.x, n3.y,
		n4.x, n4.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, SESSION->viewport->gl_data["2D Line VBO"]);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION->viewport->gl_data["2D Line Shader"];
	GL->glUseProgram(Shader);
	GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
	GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->viewport->center_2d)));
	GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->viewport->zoom_2d));

	GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(color.rgba_32()));

	GL->glBindVertexArray(SESSION->viewport->gl_data["2D Line VAO"]);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void RENDER::Dim_2D::RoundedLine(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color) {
	Line(v1, v2, width, color);
	Circle(v1, width * 0.5, color);
	Circle(v2, width * 0.5, color);
}

void RENDER::Dim_2D::Circle(const F32_V2& center, const F32& radius, const Color& color) {
	const GLuint Shader = SESSION->viewport->gl_data["2D Circle Shader"];
	GL->glUseProgram(Shader);
	GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
	GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->viewport->center_2d)));
	GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->viewport->zoom_2d));

	GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));
	GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uPosition"), 1, glm::value_ptr(center));
	GL->glUniform1f (GL->glGetUniformLocation(Shader, "uRadius"), radius);

	GL->glBindVertexArray(SESSION->viewport->gl_data["2D Circle VAO"]);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}