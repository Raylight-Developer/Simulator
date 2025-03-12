#include "Variable.hpp"

static const std::unordered_map<VARIABLE::Type, std::unordered_map<VARIABLE::Type, BinaryOp>> operations = {
	{ VARIABLE::Type::FLOAT, {
		{ VARIABLE::Type::FLOAT, [](const Variable& a, const Variable& b) { return Variable(a.get<dvec1>() + b.get<dvec1>()); } },
	{ VARIABLE::Type::INT,   [](const Variable& a, const Variable& b) { return Variable(a.get<dvec1>() + b.getCast<dvec1, qint64>()); } }
}},
	{ VARIABLE::Type::INT, {
		{ VARIABLE::Type::FLOAT, [](const Variable& a, const Variable& b) { return Variable(a.getCast<dvec1, qint64>() + b.get<dvec1>()); } },
	{ VARIABLE::Type::INT,   [](const Variable& a, const Variable& b) { return Variable(a.get<qint64>() + b.get<qint64>()); } }
}}};

Variable::Variable() :
	data(nullptr),
	type(VARIABLE::Type::NONE)
{}

Variable::~Variable() {
	delete data;
}

Variable::Variable(const dvec1& data) :
	type(VARIABLE::Type::FLOAT),
	data(new dvec1(data))
{}
Variable::Variable(const int64& data) :
	type(VARIABLE::Type::INT),
	data(new int64(data))
{}
Variable::Variable(const bool& data) :
	type(VARIABLE::Type::BOOL),
	data(new bool(data))
{}
Variable::Variable(const QString& data) :
	type(VARIABLE::Type::STRING),
	data(new QString(data))
{}
Variable::Variable(const dvec2 & data) :
	type(VARIABLE::Type::VEC2),
	data(new dvec2(data))
{}
Variable::Variable(const dvec3 & data) :
	type(VARIABLE::Type::VEC3),
	data(new dvec3(data))
{}
Variable::Variable(const dvec4 & data) :
	type(VARIABLE::Type::VEC4),
	data(new dvec4(data))
{}
Variable::Variable(const dquat & data) :
	type(VARIABLE::Type::QUAT),
	data(new dquat(data))
{}
Variable::Variable(const dmat2 & data) :
	type(VARIABLE::Type::MAT2),
	data(new dmat2(data))
{}
Variable::Variable(const dmat3 & data) :
	type(VARIABLE::Type::MAT3),
	data(new dmat3(data))
{}
Variable::Variable(const dmat4 & data) :
	type(VARIABLE::Type::MAT4),
	data(new dmat4(data))
{}

Variable Variable::operator+(const Variable & other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return Variable(get<dvec1  >() + other.get<dvec1  >());
			case VARIABLE::Type::INT   : return Variable(get<qint64 >() + other.get<qint64 >());
			case VARIABLE::Type::BOOL  : return Variable(true);
			case VARIABLE::Type::STRING: return Variable(get<QString>() + other.get<QString>());
			case VARIABLE::Type::VEC2  : return Variable(get<dvec2  >() + other.get<dvec2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<dvec3  >() + other.get<dvec3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<dvec4  >() + other.get<dvec4  >());
			case VARIABLE::Type::QUAT  : return Variable(get<dquat  >() + other.get<dquat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<dmat2  >() + other.get<dmat2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<dmat3  >() + other.get<dmat3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<dmat4  >() + other.get<dmat4  >());
		}
	}
	return Variable();
}

Variable Variable::operator-(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return Variable(get<dvec1  >() - other.get<dvec1  >());
			case VARIABLE::Type::INT   : return Variable(get<qint64 >() - other.get<qint64 >());
			case VARIABLE::Type::BOOL  : return Variable(false);
			case VARIABLE::Type::VEC2  : return Variable(get<dvec2  >() - other.get<dvec2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<dvec3  >() - other.get<dvec3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<dvec4  >() - other.get<dvec4  >());
			case VARIABLE::Type::QUAT  : return Variable(get<dquat  >() - other.get<dquat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<dmat2  >() - other.get<dmat2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<dmat3  >() - other.get<dmat3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<dmat4  >() - other.get<dmat4  >());
		}
	}
	return Variable();
}

Variable Variable::operator*(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return Variable(get<dvec1  >() * other.get<dvec1  >());
			case VARIABLE::Type::INT   : return Variable(get<qint64 >() * other.get<qint64 >());
			case VARIABLE::Type::VEC2  : return Variable(get<dvec2  >() * other.get<dvec2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<dvec3  >() * other.get<dvec3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<dvec4  >() * other.get<dvec4  >());
			case VARIABLE::Type::QUAT  : return Variable(get<dquat  >() * other.get<dquat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<dmat2  >() * other.get<dmat2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<dmat3  >() * other.get<dmat3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<dmat4  >() * other.get<dmat4  >());
		}
	}
	return Variable();
}

Variable Variable::operator/(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return Variable(get<dvec1  >() / other.get<dvec1  >());
			case VARIABLE::Type::INT   : return Variable(get<qint64 >() / other.get<qint64 >());
			case VARIABLE::Type::VEC2  : return Variable(get<dvec2  >() / other.get<dvec2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<dvec3  >() / other.get<dvec3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<dvec4  >() / other.get<dvec4  >());
			case VARIABLE::Type::MAT2  : return Variable(get<dmat2  >() / other.get<dmat2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<dmat3  >() / other.get<dmat3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<dmat4  >() / other.get<dmat4  >());
		}
	}
	return Variable();
}

bool Variable::operator==(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return get<dvec1  >() == other.get<dvec1  >();
			case VARIABLE::Type::INT   : return get<qint64 >() == other.get<qint64 >();
			case VARIABLE::Type::BOOL  : return get<bool   >() == other.get<bool   >();
			case VARIABLE::Type::STRING: return get<QString>() == other.get<QString>();
			case VARIABLE::Type::VEC2  : return get<dvec2  >() == other.get<dvec2  >();
			case VARIABLE::Type::VEC3  : return get<dvec3  >() == other.get<dvec3  >();
			case VARIABLE::Type::VEC4  : return get<dvec4  >() == other.get<dvec4  >();
			case VARIABLE::Type::QUAT  : return get<dquat  >() == other.get<dquat  >();
			case VARIABLE::Type::MAT2  : return get<dmat2  >() == other.get<dmat2  >();
			case VARIABLE::Type::MAT3  : return get<dmat3  >() == other.get<dmat3  >();
			case VARIABLE::Type::MAT4  : return get<dmat4  >() == other.get<dmat4  >();
		}
	}
	return false;
}

bool Variable::operator!=(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::FLOAT : return get<dvec1  >() != other.get<dvec1  >();
			case VARIABLE::Type::INT   : return get<qint64 >() != other.get<qint64 >();
			case VARIABLE::Type::BOOL  : return get<bool   >() != other.get<bool   >();
			case VARIABLE::Type::STRING: return get<QString>() != other.get<QString>();
			case VARIABLE::Type::VEC2  : return get<dvec2  >() != other.get<dvec2  >();
			case VARIABLE::Type::VEC3  : return get<dvec3  >() != other.get<dvec3  >();
			case VARIABLE::Type::VEC4  : return get<dvec4  >() != other.get<dvec4  >();
			case VARIABLE::Type::QUAT  : return get<dquat  >() != other.get<dquat  >();
			case VARIABLE::Type::MAT2  : return get<dmat2  >() != other.get<dmat2  >();
			case VARIABLE::Type::MAT3  : return get<dmat3  >() != other.get<dmat3  >();
			case VARIABLE::Type::MAT4  : return get<dmat4  >() != other.get<dmat4  >();
		}
	}
	return false;
}

QString Variable::to_string() const {
	switch (type) {
		case VARIABLE::Type::FLOAT: return QString::number(get<dvec1>(), 'f', 15);
		case VARIABLE::Type::INT:   return QString::number(get<int64>());
	}
	return "";
}