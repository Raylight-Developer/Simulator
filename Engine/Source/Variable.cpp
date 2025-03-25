#include "Variable.hpp"

Variable::Variable() :
	data(nullptr),
	type(VARIABLE::Type::NONE)
{}

Variable::Variable(const dvec1& data) :
	type(VARIABLE::Type::DOUBLE),
	data(data)
{}
Variable::Variable(const int64& data) :
	type(VARIABLE::Type::INT),
	data(data)
{}
Variable::Variable(const bool& data) :
	type(VARIABLE::Type::BOOL),
	data(data)
{}
Variable::Variable(const QString& data) :
	type(VARIABLE::Type::STRING),
	data(data)
{}
Variable::Variable(const dvec2 & data) :
	type(VARIABLE::Type::VEC2),
	data(data)
{}
Variable::Variable(const dvec3 & data) :
	type(VARIABLE::Type::VEC3),
	data(data)
{}
Variable::Variable(const dvec4 & data) :
	type(VARIABLE::Type::VEC4),
	data(data)
{}
Variable::Variable(const dquat & data) :
	type(VARIABLE::Type::QUAT),
	data(data)
{}
Variable::Variable(const dmat2 & data) :
	type(VARIABLE::Type::MAT2),
	data(data)
{}
Variable::Variable(const dmat3 & data) :
	type(VARIABLE::Type::MAT3),
	data(data)
{}
Variable::Variable(const dmat4 & data) :
	type(VARIABLE::Type::MAT4),
	data(data)
{}

Variable::Variable(const VARIABLE::Type & type) {
	switch (type) {
		case VARIABLE::Type::NONE  : data = nullptr          ; break;
		case VARIABLE::Type::DOUBLE: data = 0.0              ; break;
		case VARIABLE::Type::INT   : data = 0LL              ; break;
		case VARIABLE::Type::BOOL  : data = false            ; break;
		case VARIABLE::Type::STRING: data = ""               ; break;
		case VARIABLE::Type::VEC2  : data = dvec2(0)         ; break;
		case VARIABLE::Type::VEC3  : data = dvec3(0)         ; break;
		case VARIABLE::Type::VEC4  : data = dvec4(0)         ; break;
		case VARIABLE::Type::QUAT  : data = dquat(1, 0, 0, 0); break;
		case VARIABLE::Type::MAT2  : data = dmat2(0)         ; break;
		case VARIABLE::Type::MAT3  : data = dmat3(0)         ; break;
		case VARIABLE::Type::MAT4  : data = dmat4(0)         ; break;
	}
}

Variable Variable::operator+(const Variable & other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return Variable(get<dvec1  >() + other.get<dvec1  >());
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
	if (type == VARIABLE::Type::NONE and other.type != VARIABLE::Type::NONE) {
		return other;
	}
	else if (other.type == VARIABLE::Type::NONE and type != VARIABLE::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator-(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return Variable(get<dvec1  >() - other.get<dvec1  >());
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
	if (type == VARIABLE::Type::NONE and other.type != VARIABLE::Type::NONE) {
		return other;
	}
	else if (other.type == VARIABLE::Type::NONE and type != VARIABLE::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator*(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return Variable(get<dvec1  >() * other.get<dvec1  >());
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
	if (type == VARIABLE::Type::NONE and other.type != VARIABLE::Type::NONE) {
		return other;
	}
	else if (other.type == VARIABLE::Type::NONE and type != VARIABLE::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator/(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return Variable(get<dvec1  >() / other.get<dvec1  >());
			case VARIABLE::Type::INT   : return Variable(get<qint64 >() / other.get<qint64 >());
			case VARIABLE::Type::VEC2  : return Variable(get<dvec2  >() / other.get<dvec2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<dvec3  >() / other.get<dvec3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<dvec4  >() / other.get<dvec4  >());
			case VARIABLE::Type::MAT2  : return Variable(get<dmat2  >() / other.get<dmat2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<dmat3  >() / other.get<dmat3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<dmat4  >() / other.get<dmat4  >());
		}
	}
	if (type == VARIABLE::Type::NONE and other.type != VARIABLE::Type::NONE) {
		return other;
	}
	else if (other.type == VARIABLE::Type::NONE and type != VARIABLE::Type::NONE) {
		return this;
	}
	return Variable();
}

bool Variable::operator==(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<dvec1  >() == other.get<dvec1  >();
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
			case VARIABLE::Type::DOUBLE: return get<dvec1  >() != other.get<dvec1  >();
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

bool Variable::operator>(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<dvec1  >() > other.get<dvec1  >();
			case VARIABLE::Type::INT   : return get<qint64 >() > other.get<qint64 >();
			case VARIABLE::Type::STRING: return get<QString>().size() > other.get<QString>().size();
		}
	}
	return false;
}

bool Variable::operator<(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<dvec1  >() < other.get<dvec1  >();
			case VARIABLE::Type::INT   : return get<qint64 >() < other.get<qint64 >();
			case VARIABLE::Type::STRING: return get<QString>().size() < other.get<QString>().size();
		}
	}
	return false;
}

bool Variable::operator>=(const Variable& other) const {
	return (*this == other) or (*this > other);
}

bool Variable::operator<=(const Variable& other) const {
	return (*this == other) or (*this < other);
}

QString Variable::to_string() const {
	switch (type) {
		case VARIABLE::Type::DOUBLE: return QString::number(get<dvec1>(), 'f', 15);
		case VARIABLE::Type::INT   : return QString::number(get<int64>());
	}
	return "";
}

QColor VARIABLE::toColor(const VARIABLE::Type& type) {
	switch (type) {
		case VARIABLE::Type::NONE   : return QColor(175, 175, 175);
		case VARIABLE::Type::BLOCKED: return QColor(  0,   0,   0);
		case VARIABLE::Type::DOUBLE : return QColor(  0, 255,   0);
		case VARIABLE::Type::INT    : return QColor(  0, 150,   0);
		case VARIABLE::Type::BOOL   : return QColor(255, 180, 240);
		case VARIABLE::Type::STRING : return QColor(210, 145,  75);
		case VARIABLE::Type::VEC2   : return QColor(160,  80, 255);
		case VARIABLE::Type::VEC3   : return QColor(160,  80, 255);
		case VARIABLE::Type::VEC4   : return QColor(160,  80, 255);
		case VARIABLE::Type::QUAT   : return QColor(255,  80, 180);
		case VARIABLE::Type::MAT2   : return QColor(255,  80, 255);
		case VARIABLE::Type::MAT3   : return QColor(255,  80, 255);
		case VARIABLE::Type::MAT4   : return QColor(255,  80, 255);
		//case VARIABLE::Type::TRANSFORM_2D : return QColor(255, 235, 0);
		//case VARIABLE::Type::TRANSFORM_3D : return QColor(255, 235, 0);
	}
	return QColor(255, 0, 255);
}