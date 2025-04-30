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

void Variable::save(CORE::Lace& lace) const {
	lace << "Type " << VAR::toString(type) << " :: " << VAR::toString(container) << " ";
	switch (type) {
		case VAR::Type::NONE: {
			lace << "-";
			break;
		}
		case VAR::Type::DOUBLE: {
			lace << CORE::d_to_str(any_cast<F64>(data));
			break;
		}
		case VAR::Type::INT: {
			lace << to_string(any_cast<I64>(data));
			break;
		}
		case VAR::Type::BOOL: {
			lace << (any_cast<bool>(data) ? "True" : "False");
			break;
		}
		case VAR::Type::STRING: {
			lace << any_cast<QString>(data).toStdString();
			break;
		}
		case VAR::Type::VEC2: {
			const auto var = any_cast<F64_V2>(data);
			lace << var;
			break;
		}
		case VAR::Type::VEC3: {
			const auto var = any_cast<F64_V3>(data);
			lace << var;
			break;
		}
		case VAR::Type::VEC4: {
			const auto var = any_cast<F64_V4>(data);
			lace << var;
			break;
		}
		case VAR::Type::COLOR: {
			const auto var = any_cast<Color>(data);
			lace << var.r() >> var.g() >> var.b() >> var.a();
			break;
		}
		case VAR::Type::QUAT: {
			const auto var = any_cast<F64_Quat>(data);
			lace << var;
			break;
		}
		case VAR::Type::MAT2: {
			const auto var = any_cast<F64_M2>(data);
			lace << var;
			break;
		}
		case VAR::Type::MAT3: {
			const auto var = any_cast<F64_M3>(data);
			lace << var;
			break;
		}
		case VAR::Type::MAT4: {
			const auto var = any_cast<F64_M4>(data);
			lace << var;
			break;
		}
	}
}

Variable Variable::load(const Tokens& tokens) {
	Variable var;
	var.type = VAR::toType(tokens[1]);
	var.container = VAR::toContainer(tokens[3]);

	switch (var.type) {
		case VAR::Type::DOUBLE: {
			var.data = stoF64(tokens[4]);
			break;
		}
		case VAR::Type::INT: {
			var.data = stoI64(tokens[4]);
			break;
		}
		case VAR::Type::BOOL: {
			var.data = (tokens[4] == "True" ? true : false);
			break;
		}
		case VAR::Type::STRING: {
			var.data = qstr(f_join(tokens, 4, 0));
			break;
		}
		case VAR::Type::VEC2: {
			var.data = F64_V2(stoF64(tokens[4]), stoF64(tokens[5]));
			break;
		}
		case VAR::Type::VEC3: {
			var.data = F64_V3(stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]));
			break;
		}
		case VAR::Type::VEC4: {
			var.data = F64_V4(stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]), stoF64(tokens[7]));
			break;
		}
		case VAR::Type::COLOR: {
			var.data = Color(stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]), stoF64(tokens[7]));
			break;
		}
		case VAR::Type::QUAT: {
			var.data = F64_Quat(stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]), stoF64(tokens[7]));
			break;
		}
		case VAR::Type::MAT2: {
			var.data = F64_M2(
				stoF64(tokens[4]), stoF64(tokens[5]),
				stoF64(tokens[6]), stoF64(tokens[7])
			);
			break;
		}
		case VAR::Type::MAT3: {
			var.data = F64_M3(
				stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]),
				stoF64(tokens[7]), stoF64(tokens[8]), stoF64(tokens[9]),
				stoF64(tokens[10]), stoF64(tokens[11]), stoF64(tokens[12])
			);
			break;
		}
		case VAR::Type::MAT4: {
			var.data = F64_M4(
				stoF64(tokens[4]), stoF64(tokens[5]), stoF64(tokens[6]), stoF64(tokens[7]),
				stoF64(tokens[8]), stoF64(tokens[9]), stoF64(tokens[10]), stoF64(tokens[11]),
				stoF64(tokens[12]), stoF64(tokens[13]), stoF64(tokens[14]), stoF64(tokens[15]),
				stoF64(tokens[16]), stoF64(tokens[17]), stoF64(tokens[18]), stoF64(tokens[19])
			);
			break;
		}
	}

	return var;
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

string VAR::toString(const VAR::Type& value) {
	for (auto& [e, name] : type_enum_str_map) {
		if (e == value) {
			return string(name);
		}
	}
	return "NONE";
}

VAR::Type VAR::toType(const string_view& name) {
	for (auto& [e, str] : type_enum_str_map) {
		if (str == name) {
			return e;
		}
	}
	return VAR::Type::NONE;
}

string VAR::toString(const VAR::Container& value) {
	for (auto& [e, name] : container_enum_str_map) {
		if (e == value) {
			return string(name);
		}
	}
	return "NONE";
}

VAR::Container VAR::toContainer(const string_view& name) {
	for (auto& [e, str] : container_enum_str_map) {
		if (str == name) {
			return e;
		}
	}
	return VAR::Container::NONE;
}