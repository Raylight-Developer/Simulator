#include "Nodes/Variables/Constant.hpp"

#include "Session.hpp"

NODES::VARIABLE::Constant::Constant() :
	Node(Node_Type::VARIABLE_CONSTANT, "Constant")
{
	rect.setWidth(140);
	rect.setHeight(60);

	current_var_type = VAR_TYPE::NONE;
	do_var = DATA_O("", VAR_TYPE::NONE);
	value = Variable();

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	proxy_var_type = new GUI::Graphics_Widget(var_type, this);
	proxy_var_type->setPos(20, 30);
	
	expanded = rect;
	do_var->onConnection = [this](Port* port, Connection* conn) {
		rect = expanded;
		rect.setHeight(rect.height() - 20);
		proxy_var_type->setVisible(false);
		return true;
	};
	do_var->onDisconnection = [this](Port* port) {
		if (not do_var->connected()) {
			rect = expanded;
			proxy_var_type->setVisible(true);
		}
	};

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		h_setType(static_cast<VAR_TYPE>(index));
		H_GROUP(1);
	});
}

Ptr_S<Variable> NODES::VARIABLE::Constant::getData(const Port* port) {
	return make_shared<Variable>(value);
}

void NODES::VARIABLE::Constant::saveDetail(CORE::Lace& lace) const {
	lace NL;
	value.save(lace);
}

void NODES::VARIABLE::Constant::loadDetail(const Token_Array& tokens) {
	const auto temp_value = Variable::load(tokens[0]);
	setType(temp_value.type);
	setValue(temp_value);
}

void NODES::VARIABLE::Constant::h_setType(const VAR_TYPE& type) {
	H_PUSH(make_shared<Set_Type>(static_pointer_cast<Constant>(shared_from_this()), current_var_type, type, value));
}

void NODES::VARIABLE::Constant::setType(const VAR_TYPE& type) {
	proxies.clearDelete();
	if (type == VAR_TYPE::NONE) {
		rect.setHeight(60);
		proxy_var_type->setPos(20, 30);
	}
	else {
		rect.setHeight(80);
		proxy_var_type->setPos(20, 50);
	}
	rect.setWidth(140);
	do_var->rect.moveCenter(rect.topRight() + QPointF(0, 40));

	current_var_type = type;
	value = Variable(type);

	// TODO editingFinished really inconsistent
	switch (type) {
		case VAR_TYPE::DOUBLE: {
			auto input = new GUI::Double_Input();
			input->setFixedSize(100, 20);
			input->setPlaceholderText(qstr(*value.get<F64>()));
			QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input](){ const QString val = input->text(); h_setValue(Variable(val.toDouble())); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::INT: {
			auto input = new GUI::Int_Input();
			input->setFixedSize(100, 20);
			input->setPlaceholderText(qstr(*value.get<I64>()));
			QObject::connect(input, &GUI::Int_Input::editingFinished, [this, input](){ const QString val = input->text(); h_setValue(Variable(to_I64(val.toInt()))); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::BOOL: {
			auto input = new GUI::Toggle();
			input->setFixedSize(20, 20);
			input->setChecked(*value.get<bool>());

			QObject::connect(input, &GUI::Toggle::toggled, [this](bool checked) { h_setValue(Variable(checked)); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::STRING: {
			rect.setWidth(200);
			do_var->rect.moveCenter(rect.topRight() + QPointF(0, 40));

			auto input = new GUI::Value_Input();
			input->setFixedSize(160, 20);
			input->setPlaceholderText(*value.get<QString>());
			QObject::connect(input, &GUI::Value_Input::editingFinished, [this, input](){ const QString val = input->text(); h_setValue(Variable(val)); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::VEC2: {
			rect.setHeight(100);
			proxy_var_type->setPos(20, 70);

			const auto val = *value.get<F64_V2>();

			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.x));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V2>(); h_setValue(Variable(F64_V2(val.toDouble(), original->y))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 30);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.y));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V2>(); h_setValue(Variable(F64_V2(original->x, val.toDouble()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 50);
				proxies.push(proxy_input);
			}
			break;
		}
		case VAR_TYPE::VEC3: {
			rect.setHeight(120);
			proxy_var_type->setPos(20, 90);

			const auto val = *value.get<F64_V3>();

			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.x));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(val.toDouble(), original->y, original->z))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 30);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.y));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(original->x, val.toDouble(), original->z))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 50);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.z));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(original->x, original->y, val.toDouble()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 70);
				proxies.push(proxy_input);
			}
			break;
		}
		case VAR_TYPE::VEC4: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_V4>();

			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.x));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(val.toDouble(), original->y, original->z, original->w))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 30);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.y));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, val.toDouble(), original->z, original->w))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 50);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.z));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, original->y, val.toDouble(), original->w))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 70);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.w));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, original->y, original->z, val.toDouble()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 90);
				proxies.push(proxy_input);
			}
			break;
		}
		case VAR_TYPE::COLOR: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<Color>();

			{
				auto input = new GUI::Double_Input(0.0, 1.0, 5);
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.r()));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<Color>(); h_setValue(Variable(Color(val.toDouble(), original->g(), original->b(), original->a()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 30);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input(0.0, 1.0, 5);
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.g()));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), val.toDouble(), original->b(), original->a()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 50);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input(0.0, 1.0, 5);
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.b()));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), original->g(), val.toDouble(), original->a()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 70);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input(0.0, 1.0, 5);
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.a()));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), original->g(), original->b(), val.toDouble()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 90);
				proxies.push(proxy_input);
			}
			break;
		}
		case VAR_TYPE::QUAT: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_Quat>();

			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.w));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(val.toDouble(), original->x, original->y, original->z))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 30);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.x));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, val.toDouble(), original->y, original->z))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 50);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.y));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, original->x, val.toDouble(), original->z))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 70);
				proxies.push(proxy_input);
			}
			{
				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setPlaceholderText(qstr(val.z));
				QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, original->x, original->y, val.toDouble()))); H_GROUP(1); });

				PROXY(input);
				proxy_input->setPos(20, 90);
				proxies.push(proxy_input);
			}
			break;
		}
		case VAR_TYPE::MAT2: {
			rect.setHeight(100);
			proxy_var_type->setPos(20, 70);

			const auto val = *value.get<F64_M2>();

			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(50, 20);
					input->setPlaceholderText(qstr(val[0][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(F64_V2(val.toDouble(), original[0][1]), original[1]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(50, 20);
					input->setPlaceholderText(qstr(val[0][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(F64_V2(original[0][0], val.toDouble()), original[1]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 50);
					proxies.push(proxy_input);
				}

			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(50, 20);
					input->setPlaceholderText(qstr(val[1][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(original[0], F64_V2(val.toDouble(), original[0][1])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(70, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(50, 20);
					input->setPlaceholderText(qstr(val[1][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(original[0], F64_V2(original[0][0], val.toDouble())))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(70, 50);
					proxies.push(proxy_input);
				}

			}
			break;
		}
		case VAR_TYPE::MAT3: {
			rect.setWidth(160);
			do_var->rect.moveCenter(rect.topRight() + QPointF(0, 40));
			rect.setHeight(120);
			proxy_var_type->setPos(20, 90);

			const auto val = *value.get<F64_M3>();

			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(val.toDouble(), original[0][1], original[0][2]), original[1], original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(original[0][0], val.toDouble(), original[0][2]), original[1], original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(original[0][0], original[0][1], val.toDouble()), original[1], original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 70);
					proxies.push(proxy_input);
				}
			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(val.toDouble(), original[0][1], original[0][2]), original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(original[0][0], val.toDouble(), original[0][2]), original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(original[0][0], original[0][1], val.toDouble()), original[2]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 70);
					proxies.push(proxy_input);
				}
			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(val.toDouble(), original[0][1], original[0][2])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], val.toDouble(), original[0][2])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], original[0][1], val.toDouble())))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 70);
					proxies.push(proxy_input);
				}
			}
			break;
		}
		case VAR_TYPE::MAT4: {
			rect.setWidth(200);
			do_var->rect.moveCenter(rect.topRight() + QPointF(0, 40));
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_M4>();

			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 70);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[0][3]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[1], original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(20, 90);
					proxies.push(proxy_input);
				}
			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 70);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[1][3]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[2], original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(60, 90);
					proxies.push(proxy_input);
				}
			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 70);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[2][3]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[3]))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(100, 90);
					proxies.push(proxy_input);
				}
			}
			{
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[3][0]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(140, 30);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[3][1]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(140, 50);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[3][2]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3])))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(140, 70);
					proxies.push(proxy_input);
				}
				{
					auto input = new GUI::Double_Input();
					input->setFixedSize(40, 20);
					input->setPlaceholderText(qstr(val[3][3]));
					QObject::connect(input, &GUI::Double_Input::editingFinished, [this, input]() { const QString val = input->text(); const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble())))); H_GROUP(1); });

					PROXY(input);
					proxy_input->setPos(140, 90);
					proxies.push(proxy_input);
				}
			}
			break;
		}
	}

	expanded = rect;
	do_var->setType(current_var_type, VAR_CONTAINER::NONE);

	var_type->blockSignals(true);
	var_type->setCurrentIndex(static_cast<int>(current_var_type));
	var_type->blockSignals(false);
}

void NODES::VARIABLE::Constant::h_setValue(const Variable& variable) {
	H_PUSH(make_shared<Set_Value>(static_pointer_cast<Constant>(shared_from_this()), value, variable));
}

void NODES::VARIABLE::Constant::setValue(const Variable& variable) {
	value = variable;

	switch (value.type) {
		case VAR_TYPE::DOUBLE: {
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(*value.get<F64>()));
			break;
		}
		case VAR_TYPE::INT: {
			static_cast<GUI::Int_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(*value.get<I64>()));
			break;
		}
		case VAR_TYPE::BOOL: {
			static_cast<GUI::Toggle*>(proxies.ptr(0)->widget())->setCheckedInl(*value.get<bool>());
			break;
		}
		case VAR_TYPE::STRING: {
			static_cast<GUI::Value_Input*>(proxies.ptr(0)->widget())->setTextInl(*value.get<QString>());
			break;
		}
		case VAR_TYPE::VEC2: {
			const auto val = *value.get<F64_V2>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val.y));
			break;
		}
		case VAR_TYPE::VEC3: {
			const auto val = *value.get<F64_V3>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val.z));
			break;
		}
		case VAR_TYPE::VEC4: {
			const auto val = *value.get<F64_V4>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val.z));
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val.w));
			break;
		}
		case VAR_TYPE::COLOR: {
			const auto val = *value.get<Color>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val.r()));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val.g()));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val.b()));
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val.a()));
			break;
		}
		case VAR_TYPE::QUAT: {
			const auto val = *value.get<F64_Quat>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val.w));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val.z));
			break;
		}
		case VAR_TYPE::MAT2: {
			const auto val = *value.get<F64_M2>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val[0][1]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val[1][1]));
			break;
		}
		case VAR_TYPE::MAT3: {
			const auto val = *value.get<F64_M3>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val[0][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val[0][2]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(4)->widget())->setTextInl(qstr(val[1][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(5)->widget())->setTextInl(qstr(val[1][2]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr(6)->widget())->setTextInl(qstr(val[2][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(7)->widget())->setTextInl(qstr(val[2][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(8)->widget())->setTextInl(qstr(val[2][2]));
			break;
		}
		case VAR_TYPE::MAT4: {
			const auto val = *value.get<F64_M4>();
			static_cast<GUI::Double_Input*>(proxies.ptr(0)->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(1)->widget())->setTextInl(qstr(val[0][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(2)->widget())->setTextInl(qstr(val[0][2]));
			static_cast<GUI::Double_Input*>(proxies.ptr(3)->widget())->setTextInl(qstr(val[0][3]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr(4)->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(5)->widget())->setTextInl(qstr(val[1][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(6)->widget())->setTextInl(qstr(val[1][2]));
			static_cast<GUI::Double_Input*>(proxies.ptr(7)->widget())->setTextInl(qstr(val[1][3]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr( 8)->widget())->setTextInl(qstr(val[2][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr( 9)->widget())->setTextInl(qstr(val[2][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(10)->widget())->setTextInl(qstr(val[2][2]));
			static_cast<GUI::Double_Input*>(proxies.ptr(11)->widget())->setTextInl(qstr(val[2][3]));
	
			static_cast<GUI::Double_Input*>(proxies.ptr(12)->widget())->setTextInl(qstr(val[3][0]));
			static_cast<GUI::Double_Input*>(proxies.ptr(13)->widget())->setTextInl(qstr(val[3][1]));
			static_cast<GUI::Double_Input*>(proxies.ptr(14)->widget())->setTextInl(qstr(val[3][2]));
			static_cast<GUI::Double_Input*>(proxies.ptr(15)->widget())->setTextInl(qstr(val[3][3]));
			break;
		}
	}
}

NODES::VARIABLE::Constant::Set_Type::Set_Type(Ptr_S<Constant> node, const VAR_TYPE& from, const VAR_TYPE& to, const Variable& from_val) :
	CORE::CMD("Set Type"),
	node(node),
	from(from),
	from_val(from_val),
	to(to)
{}

void NODES::VARIABLE::Constant::Set_Type::execute() const {
	node->setType(to);
}

void NODES::VARIABLE::Constant::Set_Type::undo() {
	node->setType(from);
	node->setValue(from_val);
}

NODES::VARIABLE::Constant::Set_Value::Set_Value(Ptr_S<Constant> node, const Variable& from, const Variable& to) :
	CORE::CMD("Set Value"),
	node(node),
	from(from),
	to(to)
{}

void NODES::VARIABLE::Constant::Set_Value::execute() const {
	node->setValue(to);
}

void NODES::VARIABLE::Constant::Set_Value::undo() {
	node->setValue(from);
}