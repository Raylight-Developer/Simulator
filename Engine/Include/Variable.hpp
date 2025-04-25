#pragma once

#include "KL.hpp"

namespace VAR {
	enum struct Type;
}
struct Variable;

namespace VAR {
	enum struct Type {
		NONE,
		DOUBLE, INT,
		BOOL, STRING,
		VEC2, VEC3, VEC4, COLOR, QUAT, MAT2, MAT3, MAT4
		//TRANSFORM_2D, TRANSFORM_3D
	};
	enum struct Container {
		NONE, LIST
	};
	QColor toColor(const VAR::Type& type);
}

#define VAR_TYPE VAR::Type
#define VAR_CONTAINER VAR::Container

struct Variable {
	any data;
	VAR::Type type;
	VAR::Container container;

	Variable();

	Variable(const F64&      data);
	Variable(const I64&      data);
	Variable(const bool&     data);
	Variable(const QString&  data);
	Variable(const F64_V2&   data);
	Variable(const F64_V3&   data);
	Variable(const F64_V4&   data);
	Variable(const Color&    data);
	Variable(const F64_Quat& data);
	Variable(const F64_M2&   data);
	Variable(const F64_M3&   data);
	Variable(const F64_M4&   data);

	Variable(const CORE::Stack<F64>&      data);
	Variable(const CORE::Stack<I64>&      data);
	Variable(const CORE::Stack<bool>&     data);
	Variable(const CORE::Stack<QString>&  data);
	Variable(const CORE::Stack<F64_V2>&   data);
	Variable(const CORE::Stack<F64_V3>&   data);
	Variable(const CORE::Stack<F64_V4>&   data);
	Variable(const CORE::Stack<Color>&    data);
	Variable(const CORE::Stack<F64_Quat>& data);
	Variable(const CORE::Stack<F64_M2>&   data);
	Variable(const CORE::Stack<F64_M3>&   data);
	Variable(const CORE::Stack<F64_M4>&   data);

	Variable(const VAR::Type& type, const VAR::Container& container = VAR::Container::NONE);

	template <typename T>
	inline T* get() {
		return any_cast<T>(&data);
	}
};