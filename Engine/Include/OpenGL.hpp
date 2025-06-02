#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

namespace OpenGL {
	CORE::Confirm<GLuint> compileFragShader(const string& vert_file_path, const string& frag_file_path);
	CORE::Confirm<GLuint> compileFragShaderFromStr(const string& vert_file_path, const string& fragment_code);
	CORE::Confirm<GLuint> compileCompShader(const string& comp_file_path);
	bool recompileFragShader(GLuint& handle, const string& vert_file_path, const string& frag_file_path);
	bool recompileCompShader(GLuint& handle, const string& comp_file_path);
	bool checkShaderCompilation(const GLuint& shader, const string& shader_code);
	bool checkProgramLinking(const GLuint& program);
	void printShaderErrorWithContext(const string& shader_code, const string& error_str);

	struct Texture {
		GLuint handle;
		GLenum internalFormat, format, type;
		T_V2<U32> resolution;

		Texture();

		void init(const T_V2<U32>& resolution, GLenum format = GL_RGBA, GLenum type = GL_FLOAT);
		void resize(const T_V2<U32>& resolution);

		void setPixels(const T_V2<U32>& resolution, const void* data);

		static GLenum chooseInternalFormat(const GLenum& format, const GLenum& type);
	};

	struct Framebuffer {
		GLuint handle;
		Texture texture;

		Framebuffer();

		void init(const T_V2<U32>& resolution);
		void resize(const T_V2<U32>& resolution);

		void renderToSwapchain() const;
	};
}