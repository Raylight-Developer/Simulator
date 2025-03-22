#pragma once

#include "KL.hpp"

#include "Session.hpp"

namespace OpenGL {
	KL::Confirm<GLuint> f_compileFragShader(const string& vert_file_path, const string& frag_file_path);
	KL::Confirm<GLuint> f_compileCompShader(const string& comp_file_path);
	bool checkShaderCompilation(const GLuint& shader, const string& shader_code);
	bool checkProgramLinking(const GLuint& program);
	void printShaderErrorWithContext(const string& shader_code, const string& error_str);

	GLuint renderLayer(const uvec2& resolution, const GLuint& filter = GL_NEAREST);
	void   bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name);

	template <typename T>
	GLuint ssboData(const vector<T>& data) {
		GLuint buffer;
		GL->glGenBuffers(1, &buffer);
		GL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		GL->glBufferData(GL_SHADER_STORAGE_BUFFER, ul_to_u(sizeof(T) * data.size()), data.data(), GL_DYNAMIC_DRAW);
		return buffer;
	}
}