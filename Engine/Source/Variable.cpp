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
	switch (container) {
		case VAR::Container::NONE: {
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
			break;
		}
		case VAR::Container::LIST: {
			switch (type) {
				case VAR::Type::NONE  : data = nullptr                ; break;
				case VAR::Type::DOUBLE: data = CORE::Stack<F64>()     ; break;
				case VAR::Type::INT   : data = CORE::Stack<I64>()     ; break;
				case VAR::Type::BOOL  : data = CORE::Stack<bool>()    ; break;
				case VAR::Type::STRING: data = CORE::Stack<QString>() ; break;
				case VAR::Type::VEC2  : data = CORE::Stack<F64_V2>()  ; break;
				case VAR::Type::VEC3  : data = CORE::Stack<F64_V3>()  ; break;
				case VAR::Type::VEC4  : data = CORE::Stack<F64_V4>()  ; break;
				case VAR::Type::COLOR : data = CORE::Stack<Color>()   ; break;
				case VAR::Type::QUAT  : data = CORE::Stack<F64_Quat>(); break;
				case VAR::Type::MAT2  : data = CORE::Stack<F64_M2>()  ; break;
				case VAR::Type::MAT3  : data = CORE::Stack<F64_M3>()  ; break;
				case VAR::Type::MAT4  : data = CORE::Stack<F64_M4>()  ; break;
			}
			break;
		}
	}
}

void Variable::save(CORE::Lace& lace) const {
	switch (container) {
		case VAR::Container::NONE: {
			lace << "Type " << VAR::toString(type) << " :: " << VAR::toString(container) << " ";
			lace << getSingleVar();
			break;
		}
		case VAR::Container::LIST: {
			lace << "Type " << VAR::toString(type) << " :: " << VAR::toString(container) << " ( ";
			switch (type) {
				case VAR::Type::NONE: {
					lace << "0 )";
					break;
				}
				case VAR::Type::DOUBLE: {
					const auto list = any_cast<const CORE::Stack<F64>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::INT: {
					const auto list = any_cast<const CORE::Stack<I64>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::BOOL: {
					const auto list = any_cast<const CORE::Stack<bool>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace << (list->cpy(i) ? "True" : "False") << "|";
					}
					break;
				}
				case VAR::Type::STRING: {
					const auto list = any_cast<const CORE::Stack<QString>>(&data);
					lace << list->size() << " )" NL << "|BREAK|";
					for (U64 i = 0; i < list->size(); i++) {
						lace << list->cpy(i) << "|BREAK|";
					}
					break;
				}
				case VAR::Type::VEC2: {
					const auto list = any_cast<const CORE::Stack<F64_V2>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::VEC3: {
					const auto list = any_cast<const CORE::Stack<F64_V3>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::VEC4: {
					const auto list = any_cast<const CORE::Stack<F64_V4>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::COLOR: {
					const auto list = any_cast<const CORE::Stack<Color>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace << list->cpy(i).rgba() << "|";
					}
					break;
				}
				case VAR::Type::QUAT: {
					const auto list = any_cast<const CORE::Stack<F64_Quat>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::MAT2: {
					const auto list = any_cast<const CORE::Stack<F64_M2>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::MAT3: {
					const auto list = any_cast<const CORE::Stack<F64_M3>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
				case VAR::Type::MAT4: {
					const auto list = any_cast<const CORE::Stack<F64_M4>>(&data);
					lace << list->size() << " ) |";
					for (U64 i = 0; i < list->size(); i++) {
						lace SP << list->cpy(i) << " |";
					}
					break;
				}
			}
			break;
		}
	}
}

Variable Variable::load(const Tokens& tokens) {
	const auto type = VAR::toType(tokens[1]);
	const auto container = VAR::toContainer(tokens[3]);
	Variable var = Variable(type, container);

	switch (var.container) {
		case VAR::Container::NONE: {
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
			break;
		}
		case VAR::Container::LIST: {
			const U64 size = stoU64(tokens[5]);
			switch (var.type) {
				case VAR::Type::DOUBLE: {
					auto data = CORE::Stack<F64>();
					for (U64 i = 0; i < size; i += 2) {
						data.push(stoF64(tokens[8 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::INT: {
					auto data = CORE::Stack<I64>();
					for (U64 i = 0; i < size; i += 2) {
						data.push(stoI64(tokens[8 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::BOOL: {
					auto data = CORE::Stack<bool>();
					for (U64 i = 0; i < size; i += 2) {
						data.push((tokens[8 + i] == "True" ? true : false));
					}
					var.data = data;
					break;
				}
				case VAR::Type::STRING: {
					auto data = CORE::Stack<QString>();
					// TODO test
					const string delimiter = "|BREAK|";
					const string input = f_join(Tokens(tokens.begin() + size, tokens.end()));

					size_t start = delimiter.size();
					size_t end;

					while ((end = input.find(delimiter, start)) != std::string::npos) {
						data.push(qstr(input.substr(start, end - start)));
						start = end + delimiter.size();
					}

					var.data = data;
					break;
				}
				case VAR::Type::VEC2: {
					auto data = CORE::Stack<F64_V2>();
					for (U64 i = 0; i < size; i += 3) {
						data.push(F64_V2(stoF64(tokens[8 + i]), stoF64(tokens[9 + i])));
					}
					var.data = data;
					break;
				}
				case VAR::Type::VEC3: {
					auto data = CORE::Stack<F64_V3>();
					for (U64 i = 0; i < size; i += 4) {
						var.data = F64_V3(stoF64(tokens[8 + i]), stoF64(tokens[9 + i]), stoF64(tokens[10 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::VEC4: {
					auto data = CORE::Stack<F64_V4>();
					for (U64 i = 0; i < size; i += 5) {
						var.data = F64_V4(stoF64(tokens[8 + i]), stoF64(tokens[9 + i]), stoF64(tokens[10 + i]), stoF64(tokens[11 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::COLOR: {
					auto data = CORE::Stack<Color>();
					for (U64 i = 0; i < size; i += 5) {
						var.data = Color(stoF64(tokens[8 + i]), stoF64(tokens[9 + i]), stoF64(tokens[10 + i]), stoF64(tokens[11 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::QUAT: {
					auto data = CORE::Stack<F64_Quat>();
					for (U64 i = 0; i < size; i += 5) {
						var.data = F64_Quat(stoF64(tokens[8 + i]), stoF64(tokens[9 + i]), stoF64(tokens[10 + i]), stoF64(tokens[11 + i]));
					}
					var.data = data;
					break;
				}
				case VAR::Type::MAT2: {
					auto data = CORE::Stack<F64_Quat>();
					for (U64 i = 0; i < size; i += 5) {
						var.data = F64_M2(
							stoF64(tokens[ 8 + i]), stoF64(tokens[ 9 + i]),
							stoF64(tokens[10 + i]), stoF64(tokens[11 + i])
						);
					}
					var.data = data;
					break;
				}
				case VAR::Type::MAT3: {
					auto data = CORE::Stack<F64_Quat>();
					for (U64 i = 0; i < size; i += 10) {
						var.data = F64_M3(
							stoF64(tokens[ 8 + i]), stoF64(tokens[ 9 + i]), stoF64(tokens[10 + i]),
							stoF64(tokens[11 + i]), stoF64(tokens[12 + i]), stoF64(tokens[13 + i]),
							stoF64(tokens[14 + i]), stoF64(tokens[15 + i]), stoF64(tokens[16 + i])
						);
					}
					var.data = data;
					break;
				}
				case VAR::Type::MAT4: {
					auto data = CORE::Stack<F64_Quat>();
					for (U64 i = 0; i < size; i += 17) {
						var.data = F64_M4(
							stoF64(tokens[ 8 + i]), stoF64(tokens[ 9 + i]), stoF64(tokens[10 + i]), stoF64(tokens[11 + i]),
							stoF64(tokens[12 + i]), stoF64(tokens[13 + i]), stoF64(tokens[14 + i]), stoF64(tokens[15 + i]),
							stoF64(tokens[16 + i]), stoF64(tokens[17 + i]), stoF64(tokens[18 + i]), stoF64(tokens[19 + i]),
							stoF64(tokens[20 + i]), stoF64(tokens[21 + i]), stoF64(tokens[22 + i]), stoF64(tokens[23 + i])
						);
					}
					var.data = data;
					break;
				}
			}
			break;
		}
	}

	return var;
}

QString Variable::str() const {
	switch (container) {
		case VAR::Container::NONE: {
			return qstr(getSingleVar());
		}
		case VAR::Container::LIST: {
			switch (type) {
				case VAR::Type::NONE   : return "{ NULL }";
				case VAR::Type::DOUBLE : return "{ DOUBLE }";
				case VAR::Type::INT    : return "{ INT }";
				case VAR::Type::BOOL   : return "{ BOOL }";
				case VAR::Type::STRING : return "{ STRING }";
				case VAR::Type::VEC2   : return "{ VEC2 }";
				case VAR::Type::VEC3   : return "{ VEC3 }";
				case VAR::Type::VEC4   : return "{ VEC4 }";
				case VAR::Type::COLOR  : return "{ COLOR }";
				case VAR::Type::QUAT   : return "{ QUAT }";
				case VAR::Type::MAT2   : return "{ MAT2 }";
				case VAR::Type::MAT3   : return "{ MAT3 }";
				case VAR::Type::MAT4   : return "{ MAT4 }";
			}
		}
	}
	return "ERROR";
}

string Variable::getSingleVar() const {
	CORE::Lace lace;
	switch (type) {
		case VAR::Type::NONE: {
			lace << "NULL";
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
	return lace.str();
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