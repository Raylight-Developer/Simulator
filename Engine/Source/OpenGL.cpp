#include "OpenGL.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

CORE::Confirm<GLuint> OpenGL::f_compileFragShader(const string& vert_file_path, const string& frag_file_path) {
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

	GLuint shader_program = GL->glCreateProgram();
	GL->glAttachShader(shader_program, vert_shader);
	GL->glAttachShader(shader_program, frag_shader);
	GL->glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	GL->glDeleteShader(vert_shader);
	GL->glDeleteShader(frag_shader);

	return CORE::Confirm(shader_program);
}

CORE::Confirm<GLuint> OpenGL::f_compileCompShader(const string& comp_file_path) {
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

bool OpenGL::checkShaderCompilation(const GLuint& shader, const string& shader_code) {
	GLint success;
	GL->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		GL->glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		LOGL(NL << ANSI_RED << "[OpenGL]" ANSI_RESET << " Shader Compilation Failed: ");
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
		LOGL(NL << ANSI_RED << "[OpenGL]" ANSI_RESET << " Program Linking Failed: " << infoLog);
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

void OpenGL::createFbo(GLuint* FBO, GLuint* FBT, const T_V2<U64>& resolution, const GLuint& filter) {
	*FBO = 0;
	*FBT = 0;

	GL->glGenFramebuffers(1, FBO);
	GL->glBindFramebuffer(GL_FRAMEBUFFER, *FBO);

	GL->glGenTextures(1, FBT);
	GL->glBindTexture(GL_TEXTURE_2D, *FBT);
	GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, resolution.x, resolution.y, 0, GL_RGBA, GL_FLOAT, nullptr);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL->glBindTexture(GL_TEXTURE_2D, 0);

	GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *FBT, 0);

	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	GL->glDrawBuffers(1, drawBuffers);

	GLenum status = GL->glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Framebuffer incomplete: " << std::hex << status << std::endl;
	}

	GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::resizeFbo(GLuint* FBO, GLuint* FBT, const T_V2<U64>& resolution, const GLuint& filter) {
	GL->glBindFramebuffer(GL_FRAMEBUFFER, *FBO);

	GL->glDeleteTextures(1, FBT);

	GL->glGenTextures(1, FBT);
	GL->glBindTexture(GL_TEXTURE_2D, *FBT);
	GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, resolution.x, resolution.y, 0, GL_RGBA, GL_FLOAT, nullptr);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *FBT, 0);

	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	GL->glDrawBuffers(1, drawBuffers);

	GLenum status = GL->glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Framebuffer incomplete: " << std::hex << status << std::endl;
	}

	GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::createTex(GLuint* TEX, const T_V2<U64>& resolution, const GLuint& filter) {
	GL->glGenTextures(1, TEX);
	GL->glBindTexture(GL_TEXTURE_2D, *TEX);

	GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GL->glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::resizeTex(GLuint* TEX, const T_V2<U64>& resolution) {
	GL->glBindTexture(GL_TEXTURE_2D, *TEX);

	GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	GL->glBindTexture(GL_TEXTURE_2D, 0);
}

void RENDER::INIT::Screen() {
	SESSION->viewport->gl_data["Screen VAO"] = 0;
	SESSION->viewport->gl_data["Screen VBO"] = 0;
	SESSION->viewport->gl_data["Screen EBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["Screen VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["Screen VBO"];
	GLuint* EBO = &SESSION->viewport->gl_data["Screen EBO"];

	const GLfloat vertices[16] = {
		-1, -1, 0, 0,
		-1,  1, 0, 1,
		 1,  1, 1, 1,
		 1, -1, 1, 0
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

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glEnableVertexAttribArray(1);
	GL->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(GLfloat)));

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void RENDER::Dim_2D::INIT::Line() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Line.vert", "./Shaders/2D/Line.frag");
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

void RENDER::Dim_2D::INIT::Triangle() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Triangle.vert", "./Shaders/2D/Triangle.frag");
	if (confirm) {
		SESSION->viewport->gl_data["2D Triangle Shader"] = confirm.data;
	}

	SESSION->viewport->gl_data["2D Triangle VAO"] = 0;
	SESSION->viewport->gl_data["2D Triangle VBO"] = 0;
	SESSION->viewport->gl_data["2D Triangle EBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["2D Triangle VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["2D Triangle VBO"];
	GLuint* EBO = &SESSION->viewport->gl_data["2D Triangle EBO"];

	const GLfloat vertices[6] = { 0 };
	GL->glGenVertexArrays(1, VAO);
	GL->glGenBuffers(1, VBO);

	GL->glBindVertexArray(*VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void RENDER::Dim_2D::INIT::Rectangle() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Rectangle.vert", "./Shaders/2D/Rectangle.frag");
	if (confirm) {
		SESSION->viewport->gl_data["2D Rectangle Shader"] = confirm.data;
	}

	SESSION->viewport->gl_data["2D Rectangle VAO"] = 0;
	SESSION->viewport->gl_data["2D Rectangle VBO"] = 0;
	SESSION->viewport->gl_data["2D Rectangle EBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["2D Rectangle VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["2D Rectangle VBO"];
	GLuint* EBO = &SESSION->viewport->gl_data["2D Rectangle EBO"];

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

void RENDER::Dim_2D::Line(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color) {
	GL_2D_FUNC.push_back([v1, v2, width, color]() {
		const F32_V2 lineDir = glm::normalize(v2 - v1);
		const F32_V2 perpDir = F32_V2(-lineDir.y, lineDir.x);
		const F32 halfWidth = width * 0.5f;
		const F32_V2 n1 = v1 + perpDir * halfWidth;
		const F32_V2 n2 = v1 - perpDir * halfWidth;
		const F32_V2 n4 = v2 + perpDir * halfWidth;
		const F32_V2 n3 = v2 - perpDir * halfWidth;

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
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->hook.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->hook.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Line VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	});
}

void RENDER::Dim_2D::RoundedLine(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color) {
	Line(v1, v2, width, color);
	Circle(v1, width * 0.5, color);
	Circle(v2, width * 0.5, color);
}

void RENDER::Dim_2D::Circle(const F32_V2& center, const F32& radius, const Color& color) {
	GL_2D_FUNC.push_back([center, radius, color]() {
		const GLuint Shader = SESSION->viewport->gl_data["2D Circle Shader"];
		GL->glUseProgram(Shader);
		GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->hook.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->hook.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uPosition"), 1, glm::value_ptr(center));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uRadius"), radius);

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Circle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	});
}

void RENDER::Dim_2D::Triangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const Color& color) {
	GL_2D_FUNC.push_back([v1, v2, v3, color]() {
		const GLfloat vertices[6] = {
			v1.x, v1.y,
			v2.x, v2.y,
			v3.x, v3.y
		};
		GL->glBindBuffer(GL_ARRAY_BUFFER, SESSION->viewport->gl_data["2D Triangle VBO"]);
		GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render
		const GLuint Shader = SESSION->viewport->gl_data["2D Triangle Shader"];
		GL->glUseProgram(Shader);
		GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->hook.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->hook.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Triangle VAO"]);
		GL->glDrawArrays(GL_TRIANGLES, 0, 3);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	});
}

void RENDER::Dim_2D::Rectangle(const F32_V2& center, const F32& width, const F32& height, const Color& color) {
	GL_2D_FUNC.push_back([center, width, height, color]() {
		const auto h_w = width * 0.5;
		const auto h_h = height * 0.5;

		const auto v1 = F32_V2(center.x - h_w, center.y - h_h);
		const auto v2 = F32_V2(center.x - h_w, center.y + h_h);
		const auto v3 = F32_V2(center.x + h_w, center.y - h_h);
		const auto v4 = F32_V2(center.x + h_w, center.y + h_h);

		const GLfloat vertices[8] = {
			v1.x, v1.y,
			v2.x, v2.y,
			v3.x, v3.y,
			v4.x, v4.y
		};
		GL->glBindBuffer(GL_ARRAY_BUFFER, SESSION->viewport->gl_data["2D Rectangle VBO"]);
		GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render
		const GLuint Shader = SESSION->viewport->gl_data["2D Rectangle Shader"];
		GL->glUseProgram(Shader);
		GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->hook.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->hook.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Rectangle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	});
}

void RENDER::Dim_2D::Rectangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const F32_V2& v4, const Color& color) {
	GL_2D_FUNC.push_back([v1, v2, v3, v4, color]() {
		const GLfloat vertices[8] = {
			v1.x, v1.y,
			v2.x, v2.y,
			v3.x, v3.y,
			v4.x, v4.y
		};
		GL->glBindBuffer(GL_ARRAY_BUFFER, SESSION->viewport->gl_data["2D Rectangle VBO"]);
		GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render
		const GLuint Shader = SESSION->viewport->gl_data["2D Rectangle Shader"];
		GL->glUseProgram(Shader);
		GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SESSION->hook.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SESSION->hook.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Rectangle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	});
}

void RENDER::Dim_3D::INIT::Sphere() {
	const auto confirm = OpenGL::f_compileFragShader("./Shaders/Screen.vert", "./Shaders/3D/Sphere.frag");
	if (confirm) {
		SESSION->viewport->gl_data["3D Sphere Shader"] = confirm.data;
	}

	SPHERE::center_radius = new vector<F32_V4>();
	SPHERE::color = new vector<F32_V4>();

	{
		SESSION->viewport->gl_data["SSBO 0"] = 0;
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 0"];
		GL->glGenBuffers(1, SSBO);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
		GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *SSBO);
	}
	{
		SESSION->viewport->gl_data["SSBO 1"] = 0;
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 1"];
		GL->glGenBuffers(1, SSBO);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
		GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *SSBO);
	}
}

void RENDER::Dim_3D::Sphere(const F32_V3& center, const F32& radius, const Color& color) {
	SPHERE::center_radius->push_back(F32_V4(center, radius));
	SPHERE::color->push_back(color.rgba_32());
}

void RENDER::Dim_3D::renderSphere() {
	const GLuint Shader = SESSION->viewport->gl_data["3D Sphere Shader"];
	GL->glUseProgram(Shader);

	{
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 0"];
		const U64 size = SPHERE::center_radius->size() * sizeof(F32_V4);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, size, SPHERE::center_radius->data(), GL_DYNAMIC_DRAW);
	}
	{
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 1"];
		const U64 size = SPHERE::color->size() * sizeof(F32_V4);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, size, SPHERE::color->data(), GL_DYNAMIC_DRAW);
	}
	GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
	GL->glUniform1ui(GL->glGetUniformLocation(Shader, "uCount"), to_U32(SPHERE::center_radius->size()));

	GL->glBindVertexArray(SESSION->viewport->gl_data["Screen VAO"]);

	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);

	SPHERE::center_radius->clear();
	SPHERE::color->clear();
}