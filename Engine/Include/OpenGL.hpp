#pragma once

#include "KL.hpp"

namespace OpenGL {
	CORE::Confirm<GLuint> f_compileFragShader(const string& vert_file_path, const string& frag_file_path);
	CORE::Confirm<GLuint> f_compileCompShader(const string& comp_file_path);
	bool checkShaderCompilation(const GLuint& shader, const string& shader_code);
	bool checkProgramLinking(const GLuint& program);
	void printShaderErrorWithContext(const string& shader_code, const string& error_str);

	GLuint renderLayer(const T_V2<U64>& resolution, const GLuint& filter = GL_NEAREST);
	void   bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name);

	void createHQFbo(GLuint* FBO, GLuint* RBO, const T_V2<U64>& resolution, const GLuint& type = GL_UNSIGNED_BYTE);
	void resizeHQFbo(GLuint* FBO, GLuint* RBO, const T_V2<U64>& resolution, const GLuint& type = GL_UNSIGNED_BYTE);

	void createFbo(GLuint* FBO, GLuint* FBT, const T_V2<U64>& resolution, const GLuint& type = GL_UNSIGNED_BYTE, const GLuint& filter = GL_NEAREST);
	void resizeFbo(GLuint* FBO, GLuint* FBT, const T_V2<U64>& resolution, const GLuint& type = GL_UNSIGNED_BYTE, const GLuint& filter = GL_NEAREST);
}

namespace RENDER {
	namespace INIT {
		void Fbo();
	}
	namespace Dim_2D {
		namespace INIT {
			void Line();
			void Circle();
			void Triangle();
			void Rectangle();
		}
		void Line(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color = Color(1,1,1,1));
		void Circle(const F32_V2& center, const F32& radius, const Color& color = Color(1,1,1,1));
		void Triangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const Color& color = Color(1,1,1,1));
		void Rectangle(const F32_V2& center, const F32& width, const F32& height, const Color& color = Color(1,1,1,1));
		void Rectangle(const F32_V2& v1, const F32_V2& v2, const F32_V2& v3, const F32_V2& v4, const Color& color = Color(1,1,1,1));

		void RoundedLine(const F32_V2& v1, const F32_V2& v2, const F32& width, const Color& color = Color(1,1,1,1));
	}
}