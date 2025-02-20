#pragma once

#include "Include.hpp"

namespace VARIABLE {
	enum struct Type;
	enum struct Modifier;
}
struct Variable;

namespace VARIABLE {
	enum struct Type {
		NONE,
		STRING, DOUBLE, BOOL, UINT, INT,
		UMAT2, UMAT3, UMAT4, IMAT2, IMAT3, IMAT4, MAT2, MAT3, MAT4,
		UVEC2, UVEC3, UVEC4, IVEC2, IVEC3, IVEC4, VEC2, VEC3, VEC4
	};
	enum struct Modifier {
		SINGLE,
		VECTOR,
		MAP,
		POINTER
	};
}

struct Variable {
	any data;
	VARIABLE::Type type;
	VARIABLE::Modifier modifier;

	Variable();
	Variable(const any& data, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier = VARIABLE::Modifier::SINGLE);
	Variable(const string& data);
	Variable(const dvec1& data);
	Variable(const bool& data);
	Variable(const uint64& data);
	Variable(const int64& data);
	Variable(vector<dvec1> data);

	Variable operator+(const Variable& other) const;
	Variable operator-(const Variable& other) const;
	Variable operator*(const Variable& other) const;
	Variable operator/(const Variable& other) const;
	Variable pow(const Variable& other) const;

	int64  getInt()    const;
	uint64 getUint()   const;
	dvec1  getDouble() const;
	string getStr() const;

	vector<dvec1> getDoubleVector() const;

	string to_string() const;
};