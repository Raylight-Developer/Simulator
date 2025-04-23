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
#define VAR_CONATAINER VAR::Container

struct Variable {
	any data;
	VAR::Type type;

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
	Variable(const VAR::Type& type, const VAR::Container& container = VAR::Container::NONE);

	Variable operator+(const Variable& other) const;
	Variable operator-(const Variable& other) const;
	Variable operator*(const Variable& other) const;
	Variable operator/(const Variable& other) const;

	bool operator==(const Variable& other) const;
	bool operator!=(const Variable& other) const;
	bool operator> (const Variable& other) const;
	bool operator< (const Variable& other) const;
	bool operator>=(const Variable& other) const;
	bool operator<=(const Variable& other) const;

	QString to_string() const;

	template <typename T>
	inline T get() const {
		return any_cast<T>(data);
	}

	template <typename T, typename S>
	inline T getCast() const {
		return static_cast<T>(any_cast<S>(data));
	}

	template <typename T>
	inline T getInfer() const {
		switch (type) {
			case VAR::Type::DOUBLE : return static_cast<T>(any_cast<F64     >(data));
			case VAR::Type::INT    : return static_cast<T>(any_cast<I64     >(data));
			case VAR::Type::BOOL   : return static_cast<T>(any_cast<bool    >(data));
			case VAR::Type::STRING : return static_cast<T>(any_cast<QString >(data));
			case VAR::Type::VEC2   : return static_cast<T>(any_cast<F64_V2  >(data));
			case VAR::Type::VEC3   : return static_cast<T>(any_cast<F64_V3  >(data));
			case VAR::Type::VEC4   : return static_cast<T>(any_cast<F64_V4  >(data));
			case VAR::Type::COLOR  : return static_cast<T>(any_cast<Color   >(data));
			case VAR::Type::QUAT   : return static_cast<T>(any_cast<F64_Quat>(data));
			case VAR::Type::MAT2   : return static_cast<T>(any_cast<F64_M2  >(data));
			case VAR::Type::MAT3   : return static_cast<T>(any_cast<F64_M3  >(data));
			case VAR::Type::MAT4   : return static_cast<T>(any_cast<F64_M4  >(data));
		}
	}
};