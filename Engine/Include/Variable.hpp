#pragma once

#include "KL.hpp"

namespace VARIABLE {
	enum struct Type;
}
struct Variable;

namespace VARIABLE {
	enum struct Type {
		NONE, BLOCKED,
		DOUBLE, INT,
		BOOL, STRING,
		VEC2, VEC3, VEC4, COLOR, QUAT, MAT2, MAT3, MAT4
		//TRANSFORM_2D, TRANSFORM_3D
	};
	QColor toColor(const VARIABLE::Type& type);
}

#define VARIABLE_MATS VARIABLE::Type:: MAT2, VARIABLE::Type:: MAT3, VARIABLE::Type:: MAT4
#define VARIABLE_VECS VARIABLE::Type:: VEC2, VARIABLE::Type:: VEC3, VARIABLE::Type:: VEC4

#define VARIABLE_INTEGRALS VARIABLE::Type::INT, VARIABLE::Type::DOUBLE
#define VARIABLE_FULL_INTEGRALS VARIABLE_INTEGRALS, VARIABLE_VECS, VARIABLE_MATS, VARIABLE::Type::COLOR

#define VAR_TYPE VARIABLE::Type

struct Variable {
	any data;
	VARIABLE::Type type;

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
	Variable(const VARIABLE::Type& type);

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
			case VARIABLE::Type::DOUBLE : return static_cast<T>(any_cast<F64  >(data));
			case VARIABLE::Type::INT    : return static_cast<T>(any_cast<I64 >(data));
			case VARIABLE::Type::BOOL   : return static_cast<T>(any_cast<bool   >(data));
			case VARIABLE::Type::STRING : return static_cast<T>(any_cast<QString>(data));
			case VARIABLE::Type::VEC2   : return static_cast<T>(any_cast<F64_V2  >(data));
			case VARIABLE::Type::VEC3   : return static_cast<T>(any_cast<F64_V3  >(data));
			case VARIABLE::Type::VEC4   : return static_cast<T>(any_cast<F64_V4  >(data));
			case VARIABLE::Type::COLOR  : return static_cast<T>(any_cast<Color  >(data));
			case VARIABLE::Type::QUAT   : return static_cast<T>(any_cast<F64_Quat  >(data));
			case VARIABLE::Type::MAT2   : return static_cast<T>(any_cast<F64_M2  >(data));
			case VARIABLE::Type::MAT3   : return static_cast<T>(any_cast<F64_M3  >(data));
			case VARIABLE::Type::MAT4   : return static_cast<T>(any_cast<F64_M4  >(data));
		}
	}
};