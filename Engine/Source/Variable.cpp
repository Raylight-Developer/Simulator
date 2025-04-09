#include "Variable.hpp"

Variable::Variable() :
	data(nullptr),
	type(VARIABLE::Type::NONE)
{}

Variable::Variable(const F64& data) :
	type(VARIABLE::Type::DOUBLE),
	data(data)
{}
Variable::Variable(const I64& data) :
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
Variable::Variable(const F64_V2 & data) :
	type(VARIABLE::Type::VEC2),
	data(data)
{}
Variable::Variable(const F64_V3 & data) :
	type(VARIABLE::Type::VEC3),
	data(data)
{}
Variable::Variable(const F64_V4 & data) :
	type(VARIABLE::Type::VEC4),
	data(data)
{}
Variable::Variable(const Color & data) :
	type(VARIABLE::Type::COLOR),
	data(data)
{}
Variable::Variable(const F64_Quat & data) :
	type(VARIABLE::Type::QUAT),
	data(data)
{}
Variable::Variable(const F64_M2 & data) :
	type(VARIABLE::Type::MAT2),
	data(data)
{}
Variable::Variable(const F64_M3 & data) :
	type(VARIABLE::Type::MAT3),
	data(data)
{}
Variable::Variable(const F64_M4 & data) :
	type(VARIABLE::Type::MAT4),
	data(data)
{}

Variable::Variable(const VARIABLE::Type& type) :
	type(type)
{
	switch (type) {
		case VARIABLE::Type::NONE  : data = nullptr             ; break;
		case VARIABLE::Type::DOUBLE: data = 0.0                 ; break;
		case VARIABLE::Type::INT   : data = 0LL                 ; break;
		case VARIABLE::Type::BOOL  : data = false               ; break;
		case VARIABLE::Type::STRING: data = ""                  ; break;
		case VARIABLE::Type::VEC2  : data = F64_V2(0)           ; break;
		case VARIABLE::Type::VEC3  : data = F64_V3(0)           ; break;
		case VARIABLE::Type::VEC4  : data = F64_V4(0)           ; break;
		case VARIABLE::Type::COLOR : data = Color()             ; break;
		case VARIABLE::Type::QUAT  : data = F64_Quat(1, 0, 0, 0); break;
		case VARIABLE::Type::MAT2  : data = F64_M2(0)           ; break;
		case VARIABLE::Type::MAT3  : data = F64_M3(0)           ; break;
		case VARIABLE::Type::MAT4  : data = F64_M4(0)           ; break;
	}
}

Variable Variable::operator+(const Variable & other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return Variable(get<F64       >() + other.get<F64       >());
			case VARIABLE::Type::INT   : return Variable(get<I64       >() + other.get<I64       >());
			case VARIABLE::Type::BOOL  : return Variable(true);
			case VARIABLE::Type::STRING: return Variable(get<QString   >() + other.get<QString   >());
			case VARIABLE::Type::VEC2  : return Variable(get<F64_V2    >() + other.get<F64_V2    >());
			case VARIABLE::Type::VEC3  : return Variable(get<F64_V3    >() + other.get<F64_V3    >());
			case VARIABLE::Type::VEC4  : return Variable(get<F64_V4    >() + other.get<F64_V4    >());
			case VARIABLE::Type::COLOR : return Variable(get<Color     >() + other.get<Color     >());
			case VARIABLE::Type::QUAT  : return Variable(get<F64_Quat  >() + other.get<F64_Quat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<F64_M2    >() + other.get<F64_M2    >());
			case VARIABLE::Type::MAT3  : return Variable(get<F64_M3    >() + other.get<F64_M3    >());
			case VARIABLE::Type::MAT4  : return Variable(get<F64_M4    >() + other.get<F64_M4    >());
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
			case VARIABLE::Type::DOUBLE: return Variable(get<F64       >() - other.get<F64       >());
			case VARIABLE::Type::INT   : return Variable(get<I64       >() - other.get<I64       >());
			case VARIABLE::Type::BOOL  : return Variable(false);
			case VARIABLE::Type::VEC2  : return Variable(get<F64_V2    >() - other.get<F64_V2    >());
			case VARIABLE::Type::VEC3  : return Variable(get<F64_V3    >() - other.get<F64_V3    >());
			case VARIABLE::Type::VEC4  : return Variable(get<F64_V4    >() - other.get<F64_V4    >());
			case VARIABLE::Type::COLOR : return Variable(get<Color     >() - other.get<Color     >());
			case VARIABLE::Type::QUAT  : return Variable(get<F64_Quat  >() - other.get<F64_Quat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<F64_M2    >() - other.get<F64_M2    >());
			case VARIABLE::Type::MAT3  : return Variable(get<F64_M3    >() - other.get<F64_M3    >());
			case VARIABLE::Type::MAT4  : return Variable(get<F64_M4    >() - other.get<F64_M4    >());
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
			case VARIABLE::Type::DOUBLE: return Variable(get<F64       >() * other.get<F64       >());
			case VARIABLE::Type::INT   : return Variable(get<I64       >() * other.get<I64       >());
			case VARIABLE::Type::VEC2  : return Variable(get<F64_V2    >() * other.get<F64_V2    >());
			case VARIABLE::Type::VEC3  : return Variable(get<F64_V3    >() * other.get<F64_V3    >());
			case VARIABLE::Type::VEC4  : return Variable(get<F64_V4    >() * other.get<F64_V4    >());
			case VARIABLE::Type::COLOR : return Variable(get<Color     >() * other.get<Color     >());
			case VARIABLE::Type::QUAT  : return Variable(get<F64_Quat  >() * other.get<F64_Quat  >());
			case VARIABLE::Type::MAT2  : return Variable(get<F64_M2    >() * other.get<F64_M2    >());
			case VARIABLE::Type::MAT3  : return Variable(get<F64_M3    >() * other.get<F64_M3    >());
			case VARIABLE::Type::MAT4  : return Variable(get<F64_M4    >() * other.get<F64_M4    >());
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
			case VARIABLE::Type::DOUBLE: return Variable(get<F64     >() / other.get<F64     >());
			case VARIABLE::Type::INT   : return Variable(get<I64     >() / other.get<I64     >());
			case VARIABLE::Type::VEC2  : return Variable(get<F64_V2  >() / other.get<F64_V2  >());
			case VARIABLE::Type::VEC3  : return Variable(get<F64_V3  >() / other.get<F64_V3  >());
			case VARIABLE::Type::VEC4  : return Variable(get<F64_V4  >() / other.get<F64_V4  >());
			case VARIABLE::Type::MAT2  : return Variable(get<F64_M2  >() / other.get<F64_M2  >());
			case VARIABLE::Type::MAT3  : return Variable(get<F64_M3  >() / other.get<F64_M3  >());
			case VARIABLE::Type::MAT4  : return Variable(get<F64_M4  >() / other.get<F64_M4  >());
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
			case VARIABLE::Type::DOUBLE: return get<F64       >() == other.get<F64       >();
			case VARIABLE::Type::INT   : return get<I64       >() == other.get<I64       >();
			case VARIABLE::Type::BOOL  : return get<bool      >() == other.get<bool      >();
			case VARIABLE::Type::STRING: return get<QString   >() == other.get<QString   >();
			case VARIABLE::Type::VEC2  : return get<F64_V2    >() == other.get<F64_V2    >();
			case VARIABLE::Type::VEC3  : return get<F64_V3    >() == other.get<F64_V3    >();
			case VARIABLE::Type::VEC4  : return get<F64_V4    >() == other.get<F64_V4    >();
			case VARIABLE::Type::COLOR : return get<Color     >() != other.get<Color     >();
			case VARIABLE::Type::QUAT  : return get<F64_Quat  >() == other.get<F64_Quat  >();
			case VARIABLE::Type::MAT2  : return get<F64_M2    >() == other.get<F64_M2    >();
			case VARIABLE::Type::MAT3  : return get<F64_M3    >() == other.get<F64_M3    >();
			case VARIABLE::Type::MAT4  : return get<F64_M4    >() == other.get<F64_M4    >();
		}
	}
	return false;
}

bool Variable::operator!=(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<F64       >() != other.get<F64       >();
			case VARIABLE::Type::INT   : return get<I64       >() != other.get<I64       >();
			case VARIABLE::Type::BOOL  : return get<bool      >() != other.get<bool      >();
			case VARIABLE::Type::STRING: return get<QString   >() != other.get<QString   >();
			case VARIABLE::Type::VEC2  : return get<F64_V2    >() != other.get<F64_V2    >();
			case VARIABLE::Type::VEC3  : return get<F64_V3    >() != other.get<F64_V3    >();
			case VARIABLE::Type::VEC4  : return get<F64_V4    >() != other.get<F64_V4    >();
			case VARIABLE::Type::COLOR : return get<Color     >() != other.get<Color     >();
			case VARIABLE::Type::QUAT  : return get<F64_Quat  >() != other.get<F64_Quat  >();
			case VARIABLE::Type::MAT2  : return get<F64_M2    >() != other.get<F64_M2    >();
			case VARIABLE::Type::MAT3  : return get<F64_M3    >() != other.get<F64_M3    >();
			case VARIABLE::Type::MAT4  : return get<F64_M4    >() != other.get<F64_M4    >();
		}
	}
	return false;
}

bool Variable::operator>(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<F64>() > other.get<F64>();
			case VARIABLE::Type::INT   : return get<I64>() > other.get<I64>();
			case VARIABLE::Type::STRING: return get<QString>().size() > other.get<QString>().size();
		}
	}
	return false;
}

bool Variable::operator<(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VARIABLE::Type::DOUBLE: return get<F64>() < other.get<F64>();
			case VARIABLE::Type::INT   : return get<I64>() < other.get<I64>();
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
		case VARIABLE::Type::DOUBLE: return QString::number(get<F64>(), 'f', 15);
		case VARIABLE::Type::INT   : return QString::number(get<I64>());
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
		case VARIABLE::Type::STRING : return QColor(255, 150,  50);
		case VARIABLE::Type::VEC2   : return QColor(150,  50, 255);
		case VARIABLE::Type::VEC3   : return QColor(150,  50, 255);
		case VARIABLE::Type::VEC4   : return QColor(150,  50, 255);
		case VARIABLE::Type::COLOR  : return QColor(255, 255,  50);
		case VARIABLE::Type::QUAT   : return QColor(255, 150, 200);
		case VARIABLE::Type::MAT2   : return QColor(255, 100, 255);
		case VARIABLE::Type::MAT3   : return QColor(255, 100, 255);
		case VARIABLE::Type::MAT4   : return QColor(255, 100, 255);
		//case VARIABLE::Type::TRANSFORM_2D : return QColor(255, 235, 0);
		//case VARIABLE::Type::TRANSFORM_3D : return QColor(255, 235, 0);
	}
	return QColor(255, 0, 255);
}