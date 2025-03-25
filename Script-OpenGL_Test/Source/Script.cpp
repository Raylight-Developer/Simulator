#include "Script.hpp"

SCRIPT_INIT("OpenGL Script")

void Script::onLoad() {
	PRINT(NL << "Loaded OpenGL Script");

	VAO, VBO, EBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(140);
	rect.setHeight(120);

	exec_in  = new Exec_I(this, "");
	exec_out = new Exec_O(this, "");

	center = new Data_I(this, "Center", Variable(dvec2(0, 0)));
	radius = new Data_I(this, "Radius", Variable(50.0));
	color  = new Data_I(this, "Color" , Variable(dvec4(1, 1, 1, 1)));

	init();
}

void Script::onUnload() {
	PRINT(NL << "Unloaded OpenGL Script");
}

void Script::exec(const Port* port) {
	render();
	exec_out->exec();
}

void Script::init() {
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
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);
	GL->glGenBuffers(1, &EBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);

	const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Circle.vert", "./Shaders/2D/Circle.frag");
	if (confirm) {
		Shader = confirm.data;
	}
}

void Script::render() {
	const vec4 u_color  = d_to_f(color ->getData().get<dvec4>());
	const vec2 u_center = d_to_f(center->getData().get<dvec2>());
	const vec1 u_radius = d_to_f(radius->getData().get<dvec1>());

	// Render
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(session->viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(session->viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(session->viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(u_color));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uPosition"), 1, glm::value_ptr(u_center));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uRadius"), u_radius);

	GL->glBindVertexArray(VAO);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}