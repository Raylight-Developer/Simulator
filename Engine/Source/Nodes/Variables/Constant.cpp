#include "Nodes/Variables/Constant.hpp"

#include "Session.hpp"

NODES::VARIABLE::Constant::Constant() :
	Node(Node_Type::VARIABLE_CONSTANT, "Constant")
{
	rect.setWidth(140);
	rect.setHeight(60);

	current_var_type = VAR_TYPE::NONE;
	out = DATA_O("", VAR_TYPE::NONE);
	value = Variable();

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	proxy_var_type = new GUI::Graphics_Widget(var_type, this);
	proxy_var_type->setPos(20, 30);
	
	expanded = rect;
	out->onConnection = [this](Port* port, Connection* conn) {
		rect = expanded;
		rect.setHeight(rect.height() - 20);
		proxy_var_type->setVisible(false);
		return true;
	};
	out->onDisconnection = [this](Port* port) {
		if (not out->connected()) {
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
	lace NL << "┌Data";
	lace++;
	lace NL;
	value.save(lace);
	lace--;
	lace NL << "└Data";
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
	out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

	current_var_type = type;
	value = Variable(type);

	switch (type) {
		case VAR_TYPE::DOUBLE: {
			auto input = new GUI::Double_Input();
			input->setFixedSize(100, 20);
			input->setPlaceholderText(qstr(*value.get<F64>()));
			QObject::connect(input, &GUI::Double_Input::textChanged, [this](const QString val) { h_setValue(Variable(val.toDouble())); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::INT: {
			auto input = new GUI::Int_Input();
			input->setFixedSize(100, 20);
			input->setPlaceholderText(qstr(*value.get<I64>()));
			QObject::connect(input, &GUI::Int_Input::textChanged, [this](const QString val) { h_setValue(Variable(to_I64(val.toInt()))); H_GROUP(1); });

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
			out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

			auto input = new GUI::Value_Input();
			input->setFixedSize(160, 20);
			input->setPlaceholderText(*value.get<QString>());
			QObject::connect(input, &GUI::Value_Input::textChanged, [this](const QString val) { h_setValue(Variable(val)); H_GROUP(1); });

			PROXY(input);
			proxy_input->setPos(20, 30);

			proxies.push(proxy_input);
			break;
		}
		case VAR_TYPE::VEC2: {
			rect.setHeight(100);
			proxy_var_type->setPos(20, 70);

			const auto val = *value.get<F64_V2>();

			auto input_x = new GUI::Double_Input();
			input_x->setFixedSize(100, 20);
			input_x->setPlaceholderText(qstr(val.x));
			QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V2>(); h_setValue(Variable(F64_V2(val.toDouble(), original->y))); H_GROUP(1); });

			PROXY(input_x);
			proxy_input_x->setPos(20, 30);

			auto input_y = new GUI::Double_Input();
			input_y->setFixedSize(100, 20);
			input_y->setPlaceholderText(qstr(val.y));
			QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V2>(); h_setValue(Variable(F64_V2(original->x, val.toDouble()))); H_GROUP(1); });

			PROXY(input_y);
			proxy_input_y->setPos(20, 50);

			proxies.push(proxy_input_x);
			proxies.push(proxy_input_y);
			break;
		}
		case VAR_TYPE::VEC3: {
			rect.setHeight(120);
			proxy_var_type->setPos(20, 90);

			const auto val = *value.get<F64_V3>();

			auto input_x = new GUI::Double_Input();
			input_x->setFixedSize(100, 20);
			input_x->setPlaceholderText(qstr(val.x));
			QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(val.toDouble(), original->y, original->z))); H_GROUP(1); });

			PROXY(input_x);
			proxy_input_x->setPos(20, 30);

			auto input_y = new GUI::Double_Input();
			input_y->setFixedSize(100, 20);
			input_y->setPlaceholderText(qstr(val.y));
			QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(original->x, val.toDouble(), original->z))); H_GROUP(1); });

			PROXY(input_y);
			proxy_input_y->setPos(20, 50);

			auto input_z = new GUI::Double_Input();
			input_z->setFixedSize(100, 20);
			input_z->setPlaceholderText(qstr(val.z));
			QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); h_setValue(Variable(F64_V3(original->x, original->y, val.toDouble()))); H_GROUP(1); });

			PROXY(input_z);
			proxy_input_z->setPos(20, 70);

			proxies.push(proxy_input_x);
			proxies.push(proxy_input_y);
			proxies.push(proxy_input_z);
			break;
		}
		case VAR_TYPE::VEC4: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_V4>();

			auto input_x = new GUI::Double_Input();
			input_x->setFixedSize(100, 20);
			input_x->setPlaceholderText(qstr(val.x));
			QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(val.toDouble(), original->y, original->z, original->w))); H_GROUP(1); });

			PROXY(input_x);
			proxy_input_x->setPos(20, 30);

			auto input_y = new GUI::Double_Input();
			input_y->setFixedSize(100, 20);
			input_y->setPlaceholderText(qstr(val.y));
			QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, val.toDouble(), original->z, original->w))); H_GROUP(1); });

			PROXY(input_y);
			proxy_input_y->setPos(20, 50);

			auto input_z = new GUI::Double_Input();
			input_z->setFixedSize(100, 20);
			input_z->setPlaceholderText(qstr(val.z));
			QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, original->y, val.toDouble(), original->z))); H_GROUP(1); });

			PROXY(input_z);
			proxy_input_z->setPos(20, 70);

			auto input_w = new GUI::Double_Input();
			input_w->setFixedSize(100, 20);
			input_w->setPlaceholderText(qstr(val.w));
			QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_V4(original->x, original->y, original->z, val.toDouble()))); H_GROUP(1); });

			PROXY(input_w);
			proxy_input_w->setPos(20, 90);

			proxies.push(proxy_input_x);
			proxies.push(proxy_input_y);
			proxies.push(proxy_input_z);
			proxies.push(proxy_input_w);
			break;
		}
		case VAR_TYPE::COLOR: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<Color>();

			auto input_x = new GUI::Double_Input(0.0, 1.0, 5);
			input_x->setFixedSize(100, 20);
			input_x->setPlaceholderText(qstr(val.r()));
			QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); h_setValue(Variable(Color(val.toDouble(), original->g(), original->b(), original->a()))); H_GROUP(1); });

			PROXY(input_x);
			proxy_input_x->setPos(20, 30);

			auto input_y = new GUI::Double_Input(0.0, 1.0, 5);
			input_y->setFixedSize(100, 20);
			input_y->setPlaceholderText(qstr(val.g()));
			QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), val.toDouble(), original->b(), original->a()))); H_GROUP(1); });

			PROXY(input_y);
			proxy_input_y->setPos(20, 50);

			auto input_z = new GUI::Double_Input(0.0, 1.0, 5);
			input_z->setFixedSize(100, 20);
			input_z->setPlaceholderText(qstr(val.b()));
			QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), original->g(), val.toDouble(), original->a()))); H_GROUP(1); });

			PROXY(input_z);
			proxy_input_z->setPos(20, 70);

			auto input_w = new GUI::Double_Input(0.0, 1.0, 5);
			input_w->setFixedSize(100, 20);
			input_w->setPlaceholderText(qstr(val.a()));
			QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); h_setValue(Variable(Color(original->r(), original->g(), original->b(), val.toDouble()))); H_GROUP(1); });

			PROXY(input_w);
			proxy_input_w->setPos(20, 90);

			proxies.push(proxy_input_x);
			proxies.push(proxy_input_y);
			proxies.push(proxy_input_z);
			proxies.push(proxy_input_w);
			break;
		}
		case VAR_TYPE::QUAT: {
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_Quat>();

			auto input_w = new GUI::Double_Input();
			input_w->setFixedSize(100, 20);
			input_w->setPlaceholderText(qstr(val.w));
			QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(val.toDouble(), original->x, original->y, original->z))); H_GROUP(1); });

			PROXY(input_w);
			proxy_input_w->setPos(20, 30);

			auto input_x = new GUI::Double_Input();
			input_x->setFixedSize(100, 20);
			input_x->setPlaceholderText(qstr(val.x));
			QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, val.toDouble(), original->y, original->z))); H_GROUP(1); });

			PROXY(input_x);
			proxy_input_x->setPos(20, 50);

			auto input_y = new GUI::Double_Input();
			input_y->setFixedSize(100, 20);
			input_y->setPlaceholderText(qstr(val.y));
			QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, original->x, val.toDouble(), original->z))); H_GROUP(1); });

			PROXY(input_y);
			proxy_input_y->setPos(20, 70);

			auto input_z = new GUI::Double_Input();
			input_z->setFixedSize(100, 20);
			input_z->setPlaceholderText(qstr(val.z));
			QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); h_setValue(Variable(F64_Quat(original->w, original->x, original->y, val.toDouble()))); H_GROUP(1); });

			PROXY(input_z);
			proxy_input_z->setPos(20, 90);

			proxies.push(proxy_input_w);
			proxies.push(proxy_input_x);
			proxies.push(proxy_input_y);
			proxies.push(proxy_input_z);
			break;
		}
		case VAR_TYPE::MAT2: {
			rect.setHeight(100);
			proxy_var_type->setPos(20, 70);

			const auto val = *value.get<F64_M2>();

			{
				auto input_xx = new GUI::Double_Input();
				input_xx->setFixedSize(50, 20);
				input_xx->setPlaceholderText(qstr(val[0][0]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(F64_V2(val.toDouble(), original[0][1]), original[1]))); H_GROUP(1); });

				PROXY(input_xx);
				proxy_input_xx->setPos(20, 30);

				auto input_xy = new GUI::Double_Input();
				input_xy->setFixedSize(50, 20);
				input_xy->setPlaceholderText(qstr(val[0][1]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(F64_V2(original[0][0], val.toDouble()), original[1]))); H_GROUP(1); });

				PROXY(input_xy);
				proxy_input_xy->setPos(20, 50);

				proxies.push(proxy_input_xx);
				proxies.push(proxy_input_xy);
			}
			{
				auto input_yx = new GUI::Double_Input();
				input_yx->setFixedSize(50, 20);
				input_yx->setPlaceholderText(qstr(val[1][0]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(original[0], F64_V2(val.toDouble(), original[0][1])))); H_GROUP(1); });

				PROXY(input_yx);
				proxy_input_yx->setPos(70, 30);

				auto input_yy = new GUI::Double_Input();
				input_yy->setFixedSize(50, 20);
				input_yy->setPlaceholderText(qstr(val[1][1]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); h_setValue(Variable(F64_M2(original[0], F64_V2(original[0][0], val.toDouble())))); H_GROUP(1); });

				PROXY(input_yy);
				proxy_input_yy->setPos(70, 50);

				proxies.push(proxy_input_yx);
				proxies.push(proxy_input_yy);
			}
			break;
		}
		case VAR_TYPE::MAT3: {
			rect.setWidth(160);
			out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
			rect.setHeight(120);
			proxy_var_type->setPos(20, 90);

			const auto val = *value.get<F64_M3>();

			{
				auto input_xx = new GUI::Double_Input();
				input_xx->setFixedSize(40, 20);
				input_xx->setPlaceholderText(qstr(val[0][0]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(val.toDouble(), original[0][1], original[0][2]), original[1], original[2]))); H_GROUP(1); });

				PROXY(input_xx);
				proxy_input_xx->setPos(20, 30);

				auto input_xy = new GUI::Double_Input();
				input_xy->setFixedSize(40, 20);
				input_xy->setPlaceholderText(qstr(val[0][1]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(original[0][0], val.toDouble(), original[0][2]), original[1], original[2]))); H_GROUP(1); });

				PROXY(input_xy);
				proxy_input_xy->setPos(20, 50);

				auto input_xz = new GUI::Double_Input();
				input_xz->setFixedSize(40, 20);
				input_xz->setPlaceholderText(qstr(val[0][2]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(F64_V3(original[0][0], original[0][1], val.toDouble()), original[1], original[2]))); H_GROUP(1); });

				PROXY(input_xz);
				proxy_input_xz->setPos(20, 70);

				proxies.push(proxy_input_xx);
				proxies.push(proxy_input_xy);
				proxies.push(proxy_input_xz);
			}
			{
				auto input_yx = new GUI::Double_Input();
				input_yx->setFixedSize(40, 20);
				input_yx->setPlaceholderText(qstr(val[1][0]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(val.toDouble(), original[0][1], original[0][2]), original[2]))); H_GROUP(1); });

				PROXY(input_yx);
				proxy_input_yx->setPos(60, 30);

				auto input_yy = new GUI::Double_Input();
				input_yy->setFixedSize(40, 20);
				input_yy->setPlaceholderText(qstr(val[1][1]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(original[0][0], val.toDouble(), original[0][2]), original[2]))); H_GROUP(1); });

				PROXY(input_yy);
				proxy_input_yy->setPos(60, 50);

				auto input_yz = new GUI::Double_Input();
				input_yz->setFixedSize(40, 20);
				input_yz->setPlaceholderText(qstr(val[1][2]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], F64_V3(original[0][0], original[0][1], val.toDouble()), original[2]))); H_GROUP(1); });

				PROXY(input_yz);
				proxy_input_yz->setPos(60, 70);

				proxies.push(proxy_input_yx);
				proxies.push(proxy_input_yy);
				proxies.push(proxy_input_yz);
			}
			{
				auto input_zx = new GUI::Double_Input();
				input_zx->setFixedSize(40, 20);
				input_zx->setPlaceholderText(qstr(val[2][0]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(val.toDouble(), original[0][1], original[0][2])))); H_GROUP(1); });

				PROXY(input_zx);
				proxy_input_zx->setPos(100, 30);

				auto input_zy = new GUI::Double_Input();
				input_zy->setFixedSize(40, 20);
				input_zy->setPlaceholderText(qstr(val[2][1]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], val.toDouble(), original[0][2])))); H_GROUP(1); });

				PROXY(input_zy);
				proxy_input_zy->setPos(100, 50);

				auto input_zz = new GUI::Double_Input();
				input_zz->setFixedSize(40, 20);
				input_zz->setPlaceholderText(qstr(val[2][2]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); h_setValue(Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], original[0][1], val.toDouble())))); H_GROUP(1); });

				PROXY(input_zz);
				proxy_input_zz->setPos(100, 70);

				proxies.push(proxy_input_zx);
				proxies.push(proxy_input_zy);
				proxies.push(proxy_input_zz);
			}
			break;
		}
		case VAR_TYPE::MAT4: {
			rect.setWidth(200);
			out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
			rect.setHeight(140);
			proxy_var_type->setPos(20, 110);

			const auto val = *value.get<F64_M4>();

			{
				auto input_xx = new GUI::Double_Input();
				input_xx->setFixedSize(40, 20);
				input_xx->setPlaceholderText(qstr(val[0][0]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

				PROXY(input_xx);
				proxy_input_xx->setPos(20, 30);

				auto input_xy = new GUI::Double_Input();
				input_xy->setFixedSize(40, 20);
				input_xy->setPlaceholderText(qstr(val[0][1]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

				PROXY(input_xy);
				proxy_input_xy->setPos(20, 50);

				auto input_xz = new GUI::Double_Input();
				input_xz->setFixedSize(40, 20);
				input_xz->setPlaceholderText(qstr(val[0][2]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[1], original[2], original[3]))); H_GROUP(1); });

				PROXY(input_xz);
				proxy_input_xz->setPos(20, 70);

				auto input_xw = new GUI::Double_Input();
				input_xw->setFixedSize(40, 20);
				input_xw->setPlaceholderText(qstr(val[0][3]));
				QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[1], original[2], original[3]))); H_GROUP(1); });

				PROXY(input_xw);
				proxy_input_xw->setPos(20, 90);

				proxies.push(proxy_input_xx);
				proxies.push(proxy_input_xy);
				proxies.push(proxy_input_xz);
				proxies.push(proxy_input_xw);
			}
			{
				auto input_yx = new GUI::Double_Input();
				input_yx->setFixedSize(40, 20);
				input_yx->setPlaceholderText(qstr(val[1][0]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[2], original[3]))); H_GROUP(1); });

				PROXY(input_yx);
				proxy_input_yx->setPos(60, 30);

				auto input_yy = new GUI::Double_Input();
				input_yy->setFixedSize(40, 20);
				input_yy->setPlaceholderText(qstr(val[1][1]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[2], original[3]))); H_GROUP(1); });

				PROXY(input_yy);
				proxy_input_yy->setPos(60, 50);

				auto input_yz = new GUI::Double_Input();
				input_yz->setFixedSize(40, 20);
				input_yz->setPlaceholderText(qstr(val[1][2]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[2], original[3]))); H_GROUP(1); });

				PROXY(input_yz);
				proxy_input_yz->setPos(60, 70);

				auto input_yw = new GUI::Double_Input();
				input_yw->setFixedSize(40, 20);
				input_yw->setPlaceholderText(qstr(val[1][3]));
				QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[2], original[3]))); H_GROUP(1); });

				PROXY(input_yw);
				proxy_input_yw->setPos(60, 90);

				proxies.push(proxy_input_yx);
				proxies.push(proxy_input_yy);
				proxies.push(proxy_input_yz);
				proxies.push(proxy_input_yw);
			}
			{
				auto input_zx = new GUI::Double_Input();
				input_zx->setFixedSize(40, 20);
				input_zx->setPlaceholderText(qstr(val[2][0]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[3]))); H_GROUP(1); });

				PROXY(input_zx);
				proxy_input_zx->setPos(100, 30);

				auto input_zy = new GUI::Double_Input();
				input_zy->setFixedSize(40, 20);
				input_zy->setPlaceholderText(qstr(val[2][1]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[3]))); H_GROUP(1); });

				PROXY(input_zy);
				proxy_input_zy->setPos(100, 50);

				auto input_zz = new GUI::Double_Input();
				input_zz->setFixedSize(40, 20);
				input_zz->setPlaceholderText(qstr(val[2][2]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[3]))); H_GROUP(1); });

				PROXY(input_zz);
				proxy_input_zz->setPos(100, 70);

				auto input_zw = new GUI::Double_Input();
				input_zw->setFixedSize(40, 20);
				input_zw->setPlaceholderText(qstr(val[2][3]));
				QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[3]))); H_GROUP(1); });

				PROXY(input_zw);
				proxy_input_zw->setPos(100, 90);

				proxies.push(proxy_input_zx);
				proxies.push(proxy_input_zy);
				proxies.push(proxy_input_zz);
				proxies.push(proxy_input_zw);
			}
			{
				auto input_wx = new GUI::Double_Input();
				input_wx->setFixedSize(40, 20);
				input_wx->setPlaceholderText(qstr(val[3][0]));
				QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3])))); H_GROUP(1); });

				PROXY(input_wx);
				proxy_input_wx->setPos(140, 30);

				auto input_wy = new GUI::Double_Input();
				input_wy->setFixedSize(40, 20);
				input_wy->setPlaceholderText(qstr(val[3][1]));
				QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3])))); H_GROUP(1); });

				PROXY(input_wy);
				proxy_input_wy->setPos(140, 50);

				auto input_wz = new GUI::Double_Input();
				input_wz->setFixedSize(40, 20);
				input_wz->setPlaceholderText(qstr(val[3][2]));
				QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3])))); H_GROUP(1); });

				PROXY(input_wz);
				proxy_input_wz->setPos(140, 70);

				auto input_ww = new GUI::Double_Input();
				input_ww->setFixedSize(40, 20);
				input_ww->setPlaceholderText(qstr(val[3][3]));
				QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); h_setValue(Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble())))); H_GROUP(1); });

				PROXY(input_ww);
				proxy_input_ww->setPos(140, 90);

				proxies.push(proxy_input_wx);
				proxies.push(proxy_input_wy);
				proxies.push(proxy_input_wz);
				proxies.push(proxy_input_ww);
			}
			break;
		}
	}

	expanded = rect;
	out->setType(current_var_type, VAR_CONTAINER::NONE);

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
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(*value.get<F64>()));
			break;
		}
		case VAR_TYPE::INT: {
			static_cast<GUI::Int_Input*>(proxies[0]->widget())->setTextInl(qstr(*value.get<I64>()));
			break;
		}
		case VAR_TYPE::BOOL: {
			static_cast<GUI::Toggle*>(proxies[0]->widget())->setCheckedInl(*value.get<bool>());
			break;
		}
		case VAR_TYPE::STRING: {
			static_cast<GUI::Value_Input*>(proxies[0]->widget())->setTextInl(*value.get<QString>());
			break;
		}
		case VAR_TYPE::VEC2: {
			const auto val = *value.get<F64_V2>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val.y));
			break;
		}
		case VAR_TYPE::VEC3: {
			const auto val = *value.get<F64_V3>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val.z));
			break;
		}
		case VAR_TYPE::VEC4: {
			const auto val = *value.get<F64_V4>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val.z));
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val.w));
			break;
		}
		case VAR_TYPE::COLOR: {
			const auto val = *value.get<Color>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val.r()));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val.g()));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val.b()));
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val.a()));
			break;
		}
		case VAR_TYPE::QUAT: {
			const auto val = *value.get<F64_Quat>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val.w));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val.x));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val.y));
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val.z));
			break;
		}
		case VAR_TYPE::MAT2: {
			const auto val = *value.get<F64_M2>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val[0][1]));
	
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val[1][1]));
			break;
		}
		case VAR_TYPE::MAT3: {
			const auto val = *value.get<F64_M3>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val[0][1]));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val[0][2]));
	
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies[4]->widget())->setTextInl(qstr(val[1][1]));
			static_cast<GUI::Double_Input*>(proxies[5]->widget())->setTextInl(qstr(val[1][2]));
	
			static_cast<GUI::Double_Input*>(proxies[6]->widget())->setTextInl(qstr(val[2][0]));
			static_cast<GUI::Double_Input*>(proxies[7]->widget())->setTextInl(qstr(val[2][1]));
			static_cast<GUI::Double_Input*>(proxies[8]->widget())->setTextInl(qstr(val[2][2]));
			break;
		}
		case VAR_TYPE::MAT4: {
			const auto val = *value.get<F64_M4>();
			static_cast<GUI::Double_Input*>(proxies[0]->widget())->setTextInl(qstr(val[0][0]));
			static_cast<GUI::Double_Input*>(proxies[1]->widget())->setTextInl(qstr(val[0][1]));
			static_cast<GUI::Double_Input*>(proxies[2]->widget())->setTextInl(qstr(val[0][2]));
			static_cast<GUI::Double_Input*>(proxies[3]->widget())->setTextInl(qstr(val[0][3]));
	
			static_cast<GUI::Double_Input*>(proxies[4]->widget())->setTextInl(qstr(val[1][0]));
			static_cast<GUI::Double_Input*>(proxies[5]->widget())->setTextInl(qstr(val[1][1]));
			static_cast<GUI::Double_Input*>(proxies[6]->widget())->setTextInl(qstr(val[1][2]));
			static_cast<GUI::Double_Input*>(proxies[7]->widget())->setTextInl(qstr(val[1][3]));
	
			static_cast<GUI::Double_Input*>(proxies[ 8]->widget())->setTextInl(qstr(val[2][0]));
			static_cast<GUI::Double_Input*>(proxies[ 9]->widget())->setTextInl(qstr(val[2][1]));
			static_cast<GUI::Double_Input*>(proxies[10]->widget())->setTextInl(qstr(val[2][2]));
			static_cast<GUI::Double_Input*>(proxies[11]->widget())->setTextInl(qstr(val[2][3]));
	
			static_cast<GUI::Double_Input*>(proxies[12]->widget())->setTextInl(qstr(val[3][0]));
			static_cast<GUI::Double_Input*>(proxies[13]->widget())->setTextInl(qstr(val[3][1]));
			static_cast<GUI::Double_Input*>(proxies[14]->widget())->setTextInl(qstr(val[3][2]));
			static_cast<GUI::Double_Input*>(proxies[15]->widget())->setTextInl(qstr(val[3][3]));
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