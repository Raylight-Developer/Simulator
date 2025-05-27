#pragma once

#include "KL.hpp"
#include "OpenGL.hpp"

namespace RENDER {
	namespace INIT {
		void Screen();
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
	namespace Dim_3D {
		namespace INIT {
			void Sphere();
		}
		void Sphere(const F32_V3& center, const F32& radius, const Color& color = Color(1,1,1,1));
		void renderSphere();
		namespace SPHERE {
			static vector<F32_V4>* center_radius;
			static vector<F32_V4>* color;
		}
	}
}