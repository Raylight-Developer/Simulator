#pragma once

#include "KL.hpp"

namespace VAR {
	enum struct Type;
}
struct Variable;

namespace VAR {
	enum struct Type {
		NONE, BLOCKED,
		DOUBLE, INT,
		BOOL, STRING,
		VEC2, VEC3, VEC4, COLOR, QUAT, MAT2, MAT3, MAT4
		//TRANSFORM_2D, TRANSFORM_3D
	};
	enum struct Container {
		NONE, VECTOR
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

	Variable(const vector<F64>&      data);
	Variable(const vector<I64>&      data);
	Variable(const vector<bool>&     data);
	Variable(const vector<QString>&  data);
	Variable(const vector<F64_V2>&   data);
	Variable(const vector<F64_V3>&   data);
	Variable(const vector<F64_V4>&   data);
	Variable(const vector<Color>&    data);
	Variable(const vector<F64_Quat>& data);
	Variable(const vector<F64_M2>&   data);
	Variable(const vector<F64_M3>&   data);
	Variable(const vector<F64_M4>&   data);

	Variable(const VAR::Type& type, const VAR::Container& container = VAR::Container::NONE);

	template <typename T>
	inline T get() const {
		return any_cast<T>(data);
	}
};