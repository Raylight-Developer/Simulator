#pragma once

#include "KL.hpp"

namespace VARIABLE {
	enum struct Type;
}
struct Variable;

namespace VARIABLE {
	enum struct Type {
		NONE,
		FLOAT, INT,
		BOOL, STRING,
		VEC2, VEC3, VEC4, QUAT, MAT2, MAT3, MAT4,
		TRANSFORM_2D, TRANSFORM_3D
	};
	QColor toColor(const VARIABLE::Type& type);
}

#define VARIABLE_MATS VARIABLE::Type:: MAT2, VARIABLE::Type:: MAT3, VARIABLE::Type:: MAT4
#define VARIABLE_VECS VARIABLE::Type:: VEC2, VARIABLE::Type:: VEC3, VARIABLE::Type:: VEC4

#define VARIABLE_INTEGRALS VARIABLE::Type::INT, VARIABLE::Type::FLOAT
#define VARIABLE_FULL_INTEGRALS VARIABLE_INTEGRALS, VARIABLE_VECS, VARIABLE_MATS,

struct Variable {
	void* data;
	VARIABLE::Type type;

	Variable();
	~Variable();

	Variable(const dvec1&   data);
	Variable(const int64&   data);
	Variable(const bool&    data);
	Variable(const QString& data);
	Variable(const dvec2&   data);
	Variable(const dvec3&   data);
	Variable(const dvec4&   data);
	Variable(const dquat&   data);
	Variable(const dmat2&   data);
	Variable(const dmat3&   data);
	Variable(const dmat4&   data);

	Variable operator+(const Variable& other) const;
	Variable operator-(const Variable& other) const;
	Variable operator*(const Variable& other) const;
	Variable operator/(const Variable& other) const;

	bool operator==(const Variable& other) const;
	bool operator!=(const Variable& other) const;

	QString to_string() const;

	template <typename From>
	inline From get() const {
		return *static_cast<From*>(data);
	}

	template <typename To, typename From>
	inline To getCast() const {
		return static_cast<To>(*static_cast<From*>(data));
	}

	template <typename To>
	inline To getInfer() const {
		switch (type) {
			case VARIABLE::Type::FLOAT  : return static_cast<To>(*static_cast<dvec1  *>(data));
			case VARIABLE::Type::INT    : return static_cast<To>(*static_cast<qint64 *>(data));
			case VARIABLE::Type::BOOL   : return static_cast<To>(*static_cast<bool   *>(data));
			case VARIABLE::Type::STRING : return static_cast<To>(*static_cast<QString*>(data));
			case VARIABLE::Type::VEC2   : return static_cast<To>(*static_cast<dvec2  *>(data));
			case VARIABLE::Type::VEC3   : return static_cast<To>(*static_cast<dvec3  *>(data));
			case VARIABLE::Type::VEC4   : return static_cast<To>(*static_cast<dvec4  *>(data));
			case VARIABLE::Type::QUAT   : return static_cast<To>(*static_cast<dquat  *>(data));
			case VARIABLE::Type::MAT2   : return static_cast<To>(*static_cast<dmat2  *>(data));
			case VARIABLE::Type::MAT3   : return static_cast<To>(*static_cast<dmat3  *>(data));
			case VARIABLE::Type::MAT4   : return static_cast<To>(*static_cast<dmat4  *>(data));
		}
	}
};