#include "Rendering.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

void RENDER::INIT::Screen() {
	SESSION->viewport->gl_data["Screen VAO"] = 0;
	SESSION->viewport->gl_data["Screen VBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["Screen VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["Screen VBO"];

	const GLfloat vertices[12] = {
		-1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
		 3.0f, -1.0f, 2.0f, 0.0f, // Bottom-right
		-1.0f,  3.0f, 0.0f, 2.0f, // Top-left
	};
	GL->glGenVertexArrays(1, VAO);
	GL->glGenBuffers(1, VBO);

	GL->glBindVertexArray(*VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glEnableVertexAttribArray(1);
	GL->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void RENDER::Dim_2D::INIT::Line() {
	const auto confirm = OpenGL::compileFragShader("./Shaders/2D/Line.vert", "./Shaders/2D/Line.frag");
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
	const auto confirm = OpenGL::compileFragShader("./Shaders/2D/Circle.vert", "./Shaders/2D/Circle.frag");
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
	const auto confirm = OpenGL::compileFragShader("./Shaders/2D/Triangle.vert", "./Shaders/2D/Triangle.frag");
	if (confirm) {
		SESSION->viewport->gl_data["2D Triangle Shader"] = confirm.data;
	}

	SESSION->viewport->gl_data["2D Triangle VAO"] = 0;
	SESSION->viewport->gl_data["2D Triangle VBO"] = 0;
	GLuint* VAO = &SESSION->viewport->gl_data["2D Triangle VAO"];
	GLuint* VBO = &SESSION->viewport->gl_data["2D Triangle VBO"];

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
	const auto confirm = OpenGL::compileFragShader("./Shaders/2D/Rectangle.vert", "./Shaders/2D/Rectangle.frag");
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

void RENDER::Dim_2D::Line(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color, const bool& in_front) {
	auto fun = [v1, v2, width, color]() {
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
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Line VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	};
	if (in_front) {
		GL_2D_B_FUNC.push_back(fun);
	}
	else {
		GL_2D_A_FUNC.push_back(fun);
	}
}

void RENDER::Dim_2D::RoundedLine(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color, const bool& in_front) {
	Line(v1, v2, width, color, in_front);
	Circle(v1, width * 0.5, color, in_front);
	Circle(v2, width * 0.5, color, in_front);
}

void RENDER::Dim_2D::Circle(const F32_V2& center, const F32& radius, const Color& color, const bool& in_front) {
	auto fun = [center, radius, color]() {
		const GLuint Shader = SESSION->viewport->gl_data["2D Circle Shader"];
		GL->glUseProgram(Shader);
		GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uPosition"), 1, glm::value_ptr(center));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uRadius"), radius);

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Circle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	};
	if (in_front) {
		GL_2D_B_FUNC.push_back(fun);
	}
	else {
		GL_2D_A_FUNC.push_back(fun);
	}
}

void RENDER::Dim_2D::Triangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const Color& color, const bool& in_front) {
	auto fun = [v1, v2, v3, color]() {
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
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Triangle VAO"]);
		GL->glDrawArrays(GL_TRIANGLES, 0, 3);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	};
	if (in_front) {
		GL_2D_B_FUNC.push_back(fun);
	}
	else {
		GL_2D_A_FUNC.push_back(fun);
	}
}

void RENDER::Dim_2D::Rectangle(const F32_V2& center, const F32& width, const F32& height, const Color& color, const bool& in_front) {
	auto fun = [center, width, height, color]() {
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
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Rectangle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	};
	if (in_front) {
		GL_2D_B_FUNC.push_back(fun);
	}
	else {
		GL_2D_A_FUNC.push_back(fun);
	}
}

void RENDER::Dim_2D::Rectangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const F32_V2& v4, const Color& color, const bool& in_front) {
	auto fun = [v1, v2, v3, v4, color]() {
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
		GL->glUniform2fv(GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));
		GL->glUniform1f (GL->glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));

		GL->glUniform4fv(GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(color.rgba_32()));

		GL->glBindVertexArray(SESSION->viewport->gl_data["2D Rectangle VAO"]);
		GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GL->glBindVertexArray(0);
		GL->glUseProgram(0);
	};
	if (in_front) {
		GL_2D_B_FUNC.push_back(fun);
	}
	else {
		GL_2D_A_FUNC.push_back(fun);
	}
}

void RENDER::Dim_3D::INIT::Sphere() {
	const auto confirm = OpenGL::compileFragShader("./Shaders/Screen.vert", "./Shaders/3D/Sphere.frag");
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

	GL->glBindVertexArray(SESSION->viewport->gl_data["Screen VAO"]);

	{
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 0"];
		const U64 size = SPHERE::center_radius->size() * sizeof(F32_V4);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		//GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, size, SPHERE::center_radius->data(), GL_DYNAMIC_DRAW);
	}
	{
		GLuint* SSBO = &SESSION->viewport->gl_data["SSBO 1"];
		const U64 size = SPHERE::color->size() * sizeof(F32_V4);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, *SSBO);
		//GL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *SSBO);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, size, SPHERE::color->data(), GL_DYNAMIC_DRAW);
	}
	GL->glUniform2ui(GL->glGetUniformLocation(Shader, "uResolution"), SESSION->viewport->resolution.x, SESSION->viewport->resolution.y);
	GL->glUniform1ui(GL->glGetUniformLocation(Shader, "uCount"), to_U32(SPHERE::center_radius->size()));

	GL->glUniform3fv(GL->glGetUniformLocation(Shader, "uCameraPos"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_3d.position)));
	GL->glUniform3fv(GL->glGetUniformLocation(Shader, "uCameraVector"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_3d.getForwardVec())));
	GL->glUniformMatrix4fv(GL->glGetUniformLocation(Shader, "uViewMatrix"), 1, false, glm::value_ptr(to_F32(SIM_HOOK.camera_3d.getViewMatrix())));

	GL->glDrawArrays(GL_TRIANGLES, 0, 3);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);

	SPHERE::center_radius->clear();
	SPHERE::color->clear();
}