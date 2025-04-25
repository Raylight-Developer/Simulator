#include "Nodes/Variables/Constant.hpp"

#include "Session.hpp"

NODES::VARIABLE::Constant::Constant() :
	Node(Node_Type::VARIABLE_CONSTANT, "Constant")
{
	rect.setWidth(140);
	rect.setHeight(80);

	out = DATA_O("", VAR_TYPE::BLOCKED);
	value = Variable();

	current_var_type = VAR_TYPE::NONE;
	current_var_container = VAR_CONTAINER::NONE;

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Integer", "Double", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(20, 30);
	
	var_container = new GUI::Options();
	var_container->setFixedSize(100, 20);
	var_container->addItems({ "Single", "Vector"});

	PROXY(var_container);
	proxy_var_container->setPos(20, 50);

	expanded = rect;
	out->onConnRequested = [this, proxy_var_type](Port* port, Connection* conn) {
		rect = expanded;
		rect.setHeight(rect.height() - 20);
		proxy_var_type->setVisible(false);
		return true;
	};
	out->onDisconnection = [this, proxy_var_type](Port* port) {
		rect = expanded;
		proxy_var_type->setVisible(true);
	};

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this, proxy_var_type](int index) {
		switch (index) {
			case 0: {
				current_var_container = VAR_CONTAINER::NONE;
				break;
			}
			case 1: {
				current_var_container = VAR_CONTAINER::LIST;
				break;
			}
		}
		out->setType(current_var_type, current_var_container);
		value = Variable(current_var_type, current_var_container);
	});
	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this, proxy_var_type](int index) {
		proxies.clearDelete();
		if (index == 0) {
			rect.setHeight(60);
			proxy_var_type->setPos(20, 30);
		}
		else {
			rect.setHeight(80);
			proxy_var_type->setPos(20, 50);
		}
		rect.setWidth(140);
		out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

		switch (index) {
			case 0: {
				current_var_type = VAR_TYPE::BLOCKED;
				break;
			}
			case 1: {
				current_var_type = VAR_TYPE::INT;

				auto input = new GUI::Int_Input();
				input->setFixedSize(100, 20);
				input->setText("0");
				QObject::connect(input, &GUI::Int_Input::textChanged, [this](const QString val) { value = Variable(to_I64(val.toInt())); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 2: {
				current_var_type = VAR_TYPE::DOUBLE;

				auto input = new GUI::Double_Input();
				input->setFixedSize(100, 20);
				input->setText("0");
				QObject::connect(input, &GUI::Double_Input::textChanged, [this](const QString val) { value = Variable(val.toDouble()); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 3: {
				current_var_type = VAR_TYPE::BOOL;

				auto input = new GUI::Toggle();
				input->setFixedSize(20, 20);

				QObject::connect(input, &GUI::Toggle::toggled, [this](bool checked) { value = Variable(checked); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 4: {
				current_var_type = VAR_TYPE::STRING;

				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

				auto input = new GUI::Value_Input();
				input->setFixedSize(160, 20);
				input->setPlaceholderText("String");
				input->setText("");
				QObject::connect(input, &GUI::Value_Input::textChanged, [this](const QString val) { value = Variable(val); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 5: {
				current_var_type = VAR_TYPE::VEC2;

				rect.setHeight(100);
				proxy_var_type->setPos(20, 70);

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V2>(); value = Variable(F64_V2(val.toDouble(), original->y)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V2>(); value = Variable(F64_V2(original->x, val.toDouble())); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				break;
			}
			case 6: {
				current_var_type = VAR_TYPE::VEC3;

				rect.setHeight(120);
				proxy_var_type->setPos(20, 90);

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); value = Variable(F64_V3(val.toDouble(), original->y, original->z)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); value = Variable(F64_V3(original->x, val.toDouble(), original->z)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V3>(); value = Variable(F64_V3(original->x, original->y, val.toDouble())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 7: {
				current_var_type = VAR_TYPE::VEC4;

				rect.setHeight(140);
				proxy_var_type->setPos(20, 110);

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_V4(val.toDouble(), original->y, original->z, original->w)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_V4(original->x, val.toDouble(), original->z, original->w)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_V4(original->x, original->y, val.toDouble(), original->z)); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				auto input_w = new GUI::Double_Input();
				input_w->setFixedSize(100, 20);
				input_w->setText("0");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_V4(original->x, original->y, original->z, val.toDouble())); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 90);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				proxies.push(proxy_input_w);
				break;
			}
			case 8: {
				current_var_type = VAR_TYPE::COLOR;

				rect.setHeight(140);
				proxy_var_type->setPos(20, 110);

				auto input_x = new GUI::Double_Input(0.0, 1.0, 5);
				input_x->setFixedSize(100, 20);
				input_x->setText("1");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(val.toDouble(), original->g(), original->b(), original->a())); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input(0.0, 1.0, 5);
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original->r(), val.toDouble(), original->b(), original->a())); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input(0.0, 1.0, 5);
				input_z->setFixedSize(100, 20);
				input_z->setText("1");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original->r(), original->g(), val.toDouble(), original->a())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				auto input_w = new GUI::Double_Input(0.0, 1.0, 5);
				input_w->setFixedSize(100, 20);
				input_w->setText("1");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original->r(), original->g(), original->b(), val.toDouble())); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 90);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				proxies.push(proxy_input_w);
				break;
			}
			case 9: {
				current_var_type = VAR_TYPE::QUAT;

				rect.setHeight(140);
				proxy_var_type->setPos(20, 110);

				auto input_w = new GUI::Double_Input();
				input_w->setFixedSize(100, 20);
				input_w->setText("1");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_Quat(val.toDouble(), original->x, original->y, original->z)); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 30);

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_Quat(original->w, val.toDouble(), original->y, original->z)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 50);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_Quat(original->w, original->x, val.toDouble(), original->z)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 70);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<F64_V4>(); value = Variable(F64_Quat(original->w, original->x, original->y, val.toDouble())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 90);

				proxies.push(proxy_input_w);
				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 10: {
				current_var_type = VAR_TYPE::MAT2;

				rect.setHeight(100);
				proxy_var_type->setPos(20, 70);

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(50, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); value = Variable(F64_M2(F64_V2(val.toDouble(), original[0][1]), original[1])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(50, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); value = Variable(F64_M2(F64_V2(original[0][0], val.toDouble()), original[1])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
				}
				{
					auto input_yx = new GUI::Double_Input();
					input_yx->setFixedSize(50, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); value = Variable(F64_M2(original[0], F64_V2(val.toDouble(), original[0][1]))); });

					PROXY(input_yx);
					proxy_input_yx->setPos(70, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(50, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M2>(); value = Variable(F64_M2(original[0], F64_V2(original[0][0], val.toDouble()))); });

					PROXY(input_yy);
					proxy_input_yy->setPos(70, 50);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
				}
				break;
			}
			case 11: {
				current_var_type = VAR_TYPE::MAT3;

				rect.setWidth(160);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(120);
				proxy_var_type->setPos(20, 90);

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(F64_V3(val.toDouble(), original[0][1], original[0][2]), original[1], original[2])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(F64_V3(original[0][0], val.toDouble(), original[0][2]), original[1], original[2])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Double_Input();
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(F64_V3(original[0][0], original[0][1], val.toDouble()), original[1], original[2])); });

					PROXY(input_xz);
					proxy_input_xz->setPos(20, 70);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
					proxies.push(proxy_input_xz);
				}
				{
					auto input_yx = new GUI::Double_Input();
					input_yx->setFixedSize(40, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], F64_V3(val.toDouble(), original[0][1], original[0][2]), original[2])); });

					PROXY(input_yx);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], F64_V3(original[0][0], val.toDouble(), original[0][2]), original[2])); });

					PROXY(input_yy);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Double_Input();
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], F64_V3(original[0][0], original[0][1], val.toDouble()), original[2])); });

					PROXY(input_yz);
					proxy_input_yz->setPos(60, 70);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
					proxies.push(proxy_input_yz);
				}
				{
					auto input_zx = new GUI::Double_Input();
					input_zx->setFixedSize(40, 20);
					input_zx->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], original[1], F64_V3(val.toDouble(), original[0][1], original[0][2]))); });

					PROXY(input_zx);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Double_Input();
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], val.toDouble(), original[0][2]))); });

					PROXY(input_zy);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Double_Input();
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M3>(); value = Variable(F64_M3(original[0], original[1], F64_V3(original[0][0], original[0][1], val.toDouble()))); });

					PROXY(input_zz);
					proxy_input_zz->setPos(100, 70);

					proxies.push(proxy_input_zx);
					proxies.push(proxy_input_zy);
					proxies.push(proxy_input_zz);
				}
				break;
			}
			case 12: {
				current_var_type = VAR_TYPE::MAT4;

				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(140);
				proxy_var_type->setPos(20, 110);

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Double_Input();
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xz);
					proxy_input_xz->setPos(20, 70);

					auto input_xw = new GUI::Double_Input();
					input_xw->setFixedSize(40, 20);
					input_xw->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[1], original[2], original[3])); });

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
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[2], original[3])); });

					PROXY(input_yx);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[2], original[3])); });

					PROXY(input_yy);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Double_Input();
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[2], original[3])); });

					PROXY(input_yz);
					proxy_input_yz->setPos(60, 70);

					auto input_yw = new GUI::Double_Input();
					input_yw->setFixedSize(40, 20);
					input_yw->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[2], original[3])); });

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
					input_zx->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[3])); });

					PROXY(input_zx);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Double_Input();
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[3])); });

					PROXY(input_zy);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Double_Input();
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[3])); });

					PROXY(input_zz);
					proxy_input_zz->setPos(100, 70);

					auto input_zw = new GUI::Double_Input();
					input_zw->setFixedSize(40, 20);
					input_zw->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[3])); });

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
					input_wx->setText("0");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], original[2], F64_V4(val.toDouble(), original[0][1], original[0][2], original[0][3]))); });

					PROXY(input_wx);
					proxy_input_wx->setPos(140, 30);

					auto input_wy = new GUI::Double_Input();
					input_wy->setFixedSize(40, 20);
					input_wy->setText("0");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], val.toDouble(), original[0][2], original[0][3]))); });

					PROXY(input_wy);
					proxy_input_wy->setPos(140, 50);

					auto input_wz = new GUI::Double_Input();
					input_wz->setFixedSize(40, 20);
					input_wz->setText("0");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], val.toDouble(), original[0][3]))); });

					PROXY(input_wz);
					proxy_input_wz->setPos(140, 70);

					auto input_ww = new GUI::Double_Input();
					input_ww->setFixedSize(40, 20);
					input_ww->setText("1");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = *value.get<F64_M4>(); value = Variable(F64_M4(original[0], original[1], original[2], F64_V4(original[0][0], original[0][1], original[0][2], val.toDouble()))); });

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
		out->setType(current_var_type, current_var_container);
		value = Variable(current_var_type, current_var_container);
		expanded = rect;
	});
}

const Ptr_S<Variable> NODES::VARIABLE::Constant::getData(const Port* port) const {
	return make_shared<Variable>(value);
}