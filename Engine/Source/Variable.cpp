#include "Variable.hpp"

Variable::Variable() :
	data(nullptr),
	type(VAR::Type::NONE)
{}

Variable::Variable(const F64& data) :
	type(VAR::Type::DOUBLE),
	data(data)
{}
Variable::Variable(const I64& data) :
	type(VAR::Type::INT),
	data(data)
{}
Variable::Variable(const bool& data) :
	type(VAR::Type::BOOL),
	data(data)
{}
Variable::Variable(const QString& data) :
	type(VAR::Type::STRING),
	data(data)
{}
Variable::Variable(const F64_V2 & data) :
	type(VAR::Type::VEC2),
	data(data)
{}
Variable::Variable(const F64_V3 & data) :
	type(VAR::Type::VEC3),
	data(data)
{}
Variable::Variable(const F64_V4 & data) :
	type(VAR::Type::VEC4),
	data(data)
{}
Variable::Variable(const Color & data) :
	type(VAR::Type::COLOR),
	data(data)
{}
Variable::Variable(const F64_Quat & data) :
	type(VAR::Type::QUAT),
	data(data)
{}
Variable::Variable(const F64_M2 & data) :
	type(VAR::Type::MAT2),
	data(data)
{}
Variable::Variable(const F64_M3 & data) :
	type(VAR::Type::MAT3),
	data(data)
{}
Variable::Variable(const F64_M4 & data) :
	type(VAR::Type::MAT4),
	data(data)
{}

Variable::Variable(const VAR::Type& type) :
	type(type)
{
	switch (type) {
		case VAR::Type::NONE  : data = nullptr             ; break;
		case VAR::Type::DOUBLE: data = 0.0                 ; break;
		case VAR::Type::INT   : data = 0LL                 ; break;
		case VAR::Type::BOOL  : data = false               ; break;
		case VAR::Type::STRING: data = ""                  ; break;
		case VAR::Type::VEC2  : data = F64_V2(0)           ; break;
		case VAR::Type::VEC3  : data = F64_V3(0)           ; break;
		case VAR::Type::VEC4  : data = F64_V4(0)           ; break;
		case VAR::Type::COLOR : data = Color()             ; break;
		case VAR::Type::QUAT  : data = F64_Quat(1, 0, 0, 0); break;
		case VAR::Type::MAT2  : data = F64_M2(0)           ; break;
		case VAR::Type::MAT3  : data = F64_M3(0)           ; break;
		case VAR::Type::MAT4  : data = F64_M4(0)           ; break;
	}
}

Variable Variable::operator+(const Variable & other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return Variable(get<F64       >() + other.get<F64       >());
			case VAR::Type::INT   : return Variable(get<I64       >() + other.get<I64       >());
			case VAR::Type::BOOL  : return Variable(true);
			case VAR::Type::STRING: return Variable(get<QString   >() + other.get<QString   >());
			case VAR::Type::VEC2  : return Variable(get<F64_V2    >() + other.get<F64_V2    >());
			case VAR::Type::VEC3  : return Variable(get<F64_V3    >() + other.get<F64_V3    >());
			case VAR::Type::VEC4  : return Variable(get<F64_V4    >() + other.get<F64_V4    >());
			case VAR::Type::COLOR : return Variable(get<Color     >() + other.get<Color     >());
			case VAR::Type::QUAT  : return Variable(get<F64_Quat  >() + other.get<F64_Quat  >());
			case VAR::Type::MAT2  : return Variable(get<F64_M2    >() + other.get<F64_M2    >());
			case VAR::Type::MAT3  : return Variable(get<F64_M3    >() + other.get<F64_M3    >());
			case VAR::Type::MAT4  : return Variable(get<F64_M4    >() + other.get<F64_M4    >());
		}
	}
	if (type == VAR::Type::NONE and other.type != VAR::Type::NONE) {
		return other;
	}
	else if (other.type == VAR::Type::NONE and type != VAR::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator-(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return Variable(get<F64       >() - other.get<F64       >());
			case VAR::Type::INT   : return Variable(get<I64       >() - other.get<I64       >());
			case VAR::Type::BOOL  : return Variable(false);
			case VAR::Type::VEC2  : return Variable(get<F64_V2    >() - other.get<F64_V2    >());
			case VAR::Type::VEC3  : return Variable(get<F64_V3    >() - other.get<F64_V3    >());
			case VAR::Type::VEC4  : return Variable(get<F64_V4    >() - other.get<F64_V4    >());
			case VAR::Type::COLOR : return Variable(get<Color     >() - other.get<Color     >());
			case VAR::Type::QUAT  : return Variable(get<F64_Quat  >() - other.get<F64_Quat  >());
			case VAR::Type::MAT2  : return Variable(get<F64_M2    >() - other.get<F64_M2    >());
			case VAR::Type::MAT3  : return Variable(get<F64_M3    >() - other.get<F64_M3    >());
			case VAR::Type::MAT4  : return Variable(get<F64_M4    >() - other.get<F64_M4    >());
		}
	}
	if (type == VAR::Type::NONE and other.type != VAR::Type::NONE) {
		return other;
	}
	else if (other.type == VAR::Type::NONE and type != VAR::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator*(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return Variable(get<F64       >() * other.get<F64       >());
			case VAR::Type::INT   : return Variable(get<I64       >() * other.get<I64       >());
			case VAR::Type::VEC2  : return Variable(get<F64_V2    >() * other.get<F64_V2    >());
			case VAR::Type::VEC3  : return Variable(get<F64_V3    >() * other.get<F64_V3    >());
			case VAR::Type::VEC4  : return Variable(get<F64_V4    >() * other.get<F64_V4    >());
			case VAR::Type::COLOR : return Variable(get<Color     >() * other.get<Color     >());
			case VAR::Type::QUAT  : return Variable(get<F64_Quat  >() * other.get<F64_Quat  >());
			case VAR::Type::MAT2  : return Variable(get<F64_M2    >() * other.get<F64_M2    >());
			case VAR::Type::MAT3  : return Variable(get<F64_M3    >() * other.get<F64_M3    >());
			case VAR::Type::MAT4  : return Variable(get<F64_M4    >() * other.get<F64_M4    >());
		}
	}
	if (type == VAR::Type::NONE and other.type != VAR::Type::NONE) {
		return other;
	}
	else if (other.type == VAR::Type::NONE and type != VAR::Type::NONE) {
		return this;
	}
	return Variable();
}

Variable Variable::operator/(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return Variable(get<F64     >() / other.get<F64     >());
			case VAR::Type::INT   : return Variable(get<I64     >() / other.get<I64     >());
			case VAR::Type::VEC2  : return Variable(get<F64_V2  >() / other.get<F64_V2  >());
			case VAR::Type::VEC3  : return Variable(get<F64_V3  >() / other.get<F64_V3  >());
			case VAR::Type::VEC4  : return Variable(get<F64_V4  >() / other.get<F64_V4  >());
			case VAR::Type::MAT2  : return Variable(get<F64_M2  >() / other.get<F64_M2  >());
			case VAR::Type::MAT3  : return Variable(get<F64_M3  >() / other.get<F64_M3  >());
			case VAR::Type::MAT4  : return Variable(get<F64_M4  >() / other.get<F64_M4  >());
		}
	}
	if (type == VAR::Type::NONE and other.type != VAR::Type::NONE) {
		return other;
	}
	else if (other.type == VAR::Type::NONE and type != VAR::Type::NONE) {
		return this;
	}
	return Variable();
}

bool Variable::operator==(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return get<F64       >() == other.get<F64       >();
			case VAR::Type::INT   : return get<I64       >() == other.get<I64       >();
			case VAR::Type::BOOL  : return get<bool      >() == other.get<bool      >();
			case VAR::Type::STRING: return get<QString   >() == other.get<QString   >();
			case VAR::Type::VEC2  : return get<F64_V2    >() == other.get<F64_V2    >();
			case VAR::Type::VEC3  : return get<F64_V3    >() == other.get<F64_V3    >();
			case VAR::Type::VEC4  : return get<F64_V4    >() == other.get<F64_V4    >();
			case VAR::Type::COLOR : return get<Color     >() != other.get<Color     >();
			case VAR::Type::QUAT  : return get<F64_Quat  >() == other.get<F64_Quat  >();
			case VAR::Type::MAT2  : return get<F64_M2    >() == other.get<F64_M2    >();
			case VAR::Type::MAT3  : return get<F64_M3    >() == other.get<F64_M3    >();
			case VAR::Type::MAT4  : return get<F64_M4    >() == other.get<F64_M4    >();
		}
	}
	return false;
}

bool Variable::operator!=(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return get<F64       >() != other.get<F64       >();
			case VAR::Type::INT   : return get<I64       >() != other.get<I64       >();
			case VAR::Type::BOOL  : return get<bool      >() != other.get<bool      >();
			case VAR::Type::STRING: return get<QString   >() != other.get<QString   >();
			case VAR::Type::VEC2  : return get<F64_V2    >() != other.get<F64_V2    >();
			case VAR::Type::VEC3  : return get<F64_V3    >() != other.get<F64_V3    >();
			case VAR::Type::VEC4  : return get<F64_V4    >() != other.get<F64_V4    >();
			case VAR::Type::COLOR : return get<Color     >() != other.get<Color     >();
			case VAR::Type::QUAT  : return get<F64_Quat  >() != other.get<F64_Quat  >();
			case VAR::Type::MAT2  : return get<F64_M2    >() != other.get<F64_M2    >();
			case VAR::Type::MAT3  : return get<F64_M3    >() != other.get<F64_M3    >();
			case VAR::Type::MAT4  : return get<F64_M4    >() != other.get<F64_M4    >();
		}
	}
	return false;
}

bool Variable::operator>(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return get<F64>() > other.get<F64>();
			case VAR::Type::INT   : return get<I64>() > other.get<I64>();
			case VAR::Type::STRING: return get<QString>().size() > other.get<QString>().size();
		}
	}
	return false;
}

bool Variable::operator<(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
			case VAR::Type::DOUBLE: return get<F64>() < other.get<F64>();
			case VAR::Type::INT   : return get<I64>() < other.get<I64>();
			case VAR::Type::STRING: return get<QString>().size() < other.get<QString>().size();
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
		case VAR::Type::DOUBLE: return QString::number(get<F64>(), 'f', 15);
		case VAR::Type::INT   : return QString::number(get<I64>());
	}
	return "";
}

QColor VAR::toColor(const VAR::Type& type) {
	switch (type) {
		case VAR::Type::NONE   : return QColor(175, 175, 175);
		case VAR::Type::BLOCKED: return QColor(  0,   0,   0);
		case VAR::Type::DOUBLE : return QColor(  0, 255,   0);
		case VAR::Type::INT    : return QColor(  0, 150,   0);
		case VAR::Type::BOOL   : return QColor(255, 180, 240);
		case VAR::Type::STRING : return QColor(255, 150,  50);
		case VAR::Type::VEC2   : return QColor(150,  50, 255);
		case VAR::Type::VEC3   : return QColor(150,  50, 255);
		case VAR::Type::VEC4   : return QColor(150,  50, 255);
		case VAR::Type::COLOR  : return QColor(255, 255,  50);
		case VAR::Type::QUAT   : return QColor(255, 150, 200);
		case VAR::Type::MAT2   : return QColor(255, 100, 255);
		case VAR::Type::MAT3   : return QColor(255, 100, 255);
		case VAR::Type::MAT4   : return QColor(255, 100, 255);
		//case VAR::Type::TRANSFORM_2D : return QColor(255, 235, 0);
		//case VAR::Type::TRANSFORM_3D : return QColor(255, 235, 0);
	}
	return QColor(255, 0, 255);
}