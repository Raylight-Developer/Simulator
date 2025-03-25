#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script();

	void onLoad() override;
	void onUnload() override;

	void exec(const Port* port) override;

	Exec_I* exec_in;
	Exec_O* exec_out;

	Data_I* center;
	Data_I* radius;
	Data_I* color;

	GLuint VAO, VBO, EBO, Shader;

	void init();
	void render();
};