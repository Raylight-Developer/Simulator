#include "Variable.hpp"

Variable::Variable() :
	data(nullptr),
	type(VAR::Type::NONE),
	container(VAR::Container::NONE)
{}

Variable::Variable(const F64& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::DOUBLE),
	data(data)
{}
Variable::Variable(const I64& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::INT),
	data(data)
{}
Variable::Variable(const bool& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::BOOL),
	data(data)
{}
Variable::Variable(const QString& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::STRING),
	data(data)
{}
Variable::Variable(const F64_V2& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::VEC2),
	data(data)
{}
Variable::Variable(const F64_V3& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::VEC3),
	data(data)
{}
Variable::Variable(const F64_V4& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::VEC4),
	data(data)
{}
Variable::Variable(const Color& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::COLOR),
	data(data)
{}
Variable::Variable(const F64_Quat& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::QUAT),
	data(data)
{}
Variable::Variable(const F64_M2& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::MAT2),
	data(data)
{}
Variable::Variable(const F64_M3& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::MAT3),
	data(data)
{}
Variable::Variable(const F64_M4& data) :
	container(VAR::Container::NONE),
	type(VAR::Type::MAT4),
	data(data)
{}

Variable::Variable(const CORE::Stack<F64>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::DOUBLE),
	data(data)
{}
Variable::Variable(const CORE::Stack<I64>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::INT),
	data(data)
{}
Variable::Variable(const CORE::Stack<bool>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::BOOL),
	data(data)
{}
Variable::Variable(const CORE::Stack<QString>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::STRING),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_V2>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::VEC2),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_V3>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::VEC3),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_V4>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::VEC4),
	data(data)
{}
Variable::Variable(const CORE::Stack<Color>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::COLOR),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_Quat>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::QUAT),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_M2>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::MAT2),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_M3>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::MAT3),
	data(data)
{}
Variable::Variable(const CORE::Stack<F64_M4>& data) :
	container(VAR::Container::LIST),
	type(VAR::Type::MAT4),
	data(data)
{}

Variable::Variable(const VAR::Type& type, const VAR::Container& container) :
	type(type),
	container(container)
{
	switch (type) {
		case VAR::Type::NONE  : data = nullptr             ; break;
		case VAR::Type::DOUBLE: data = 0.0                 ; break;
		case VAR::Type::INT   : data = 0LL                 ; break;
		case VAR::Type::BOOL  : data = false               ; break;
		case VAR::Type::STRING: data = QString()           ; break;
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

QColor VAR::toColor(const VAR::Type& type) {
	switch (type) {
		case VAR::Type::NONE   : return QColor( 50,  50,  50);
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