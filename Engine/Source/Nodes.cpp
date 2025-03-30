#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

#define DATA_I(label, type) new PORT::Data_I(this, label, type);
#define DATA_O(label, type) new PORT::Data_O(this, label, type);
#define EXEC_I(label) new PORT::Exec_I(this, label);
#define EXEC_O(label) new PORT::Exec_O(this, label);

#define PROXY(widget) auto* proxy_##widget = new GUI::Graphics_Widget(widget, this)
#define GET_DATA(type) getData().get<type>()

NODES::VARIABLES::Constant::Constant() :
	Node("Constant")
{
	rect.setWidth(140);
	rect.setHeight(60);

	out = DATA_O("", VAR_TYPE::BLOCKED);
	value = Variable();

	enums = new GUI::Options();
	enums->setFixedSize(100, 20);
	enums->addItems({ "", "Integer", "Double", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(enums);
	proxy_enums->setPos(20, 30);

	expanded = rect;
	out->onConnRequested = [this, proxy_enums](Port* port, Connection* conn) {
		rect = expanded;
		rect.setHeight(rect.height() - 20);
		proxy_enums->setVisible(false);
		return true;
	};
	out->onDisconnection = [this, proxy_enums](Port* port) {
		rect = expanded;
		proxy_enums->setVisible(true);
	};

	QObject::connect(enums, &GUI::Options::currentIndexChanged, [this, proxy_enums](int index) {
		proxies.clearDelete();
		if (index == 0) {
			rect.setHeight(60);
			proxy_enums->setPos(20, 30);
		}
		else {
			rect.setHeight(80);
			proxy_enums->setPos(20, 50);
		}
		rect.setWidth(140);
		out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

		switch (index) {
			case 0: {
				out->setType(VAR_TYPE::BLOCKED);
				value = Variable();
				break;
			}
			case 1: {
				out->setType(VAR_TYPE::INT);
				value = Variable(0LL);

				auto input = new GUI::Int_Input();
				input->setFixedSize(100, 20);
				input->setText("0");
				QObject::connect(input, &GUI::Int_Input::textChanged, [this](const QString val) { value = Variable(i_to_il(val.toInt())); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 2: {
				out->setType(VAR_TYPE::DOUBLE);
				value = Variable(0.0);

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
				out->setType(VAR_TYPE::BOOL);
				value = Variable(false);

				auto input = new GUI::Toggle();
				input->setFixedSize(20, 20);

				QObject::connect(input, &GUI::Toggle::toggled, [this](bool checked) { value = Variable(checked); });

				PROXY(input);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 4: {
				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

				out->setType(VAR_TYPE::STRING);
				value = Variable(0.0);

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
				rect.setHeight(100);
				proxy_enums->setPos(20, 70);

				out->setType(VAR_TYPE::VEC2);
				value = Variable(dvec2(0.0));

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec2>(); value = Variable(dvec2(val.toDouble(), original.y)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec2>(); value = Variable(dvec2(original.x, val.toDouble())); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				break;
			}
			case 6: {
				rect.setHeight(120);
				proxy_enums->setPos(20, 90);

				out->setType(VAR_TYPE::VEC3);
				value = Variable(dvec3(0.0));

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(val.toDouble(), original.y, original.z)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(original.x, val.toDouble(), original.z)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(original.x, original.y, val.toDouble())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 7: {
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VAR_TYPE::VEC4);
				value = Variable(dvec4(0.0));

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(val.toDouble(), original.y, original.z, original.w)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, val.toDouble(), original.z, original.w)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, original.y, val.toDouble(), original.z)); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				auto input_w = new GUI::Double_Input();
				input_w->setFixedSize(100, 20);
				input_w->setText("0");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, original.y, original.z, val.toDouble())); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 90);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				proxies.push(proxy_input_w);
				break;
			}
			case 8: {
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VAR_TYPE::COLOR);
				value = Variable(Color(1, 0, 1, 1));

				auto input_x = new GUI::Double_Input(0.0, 1.0, 5);
				input_x->setFixedSize(100, 20);
				input_x->setText("1");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(val.toDouble(), original.g(), original.b(), original.a())); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Double_Input(0.0, 1.0, 5);
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original.r(), val.toDouble(), original.b(), original.a())); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Double_Input(0.0, 1.0, 5);
				input_z->setFixedSize(100, 20);
				input_z->setText("1");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original.r(), original.g(), val.toDouble(), original.a())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 70);

				auto input_w = new GUI::Double_Input(0.0, 1.0, 5);
				input_w->setFixedSize(100, 20);
				input_w->setText("1");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<Color>(); value = Variable(Color(original.r(), original.g(), original.b(), val.toDouble())); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 90);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				proxies.push(proxy_input_w);
				break;
			}
			case 9: {
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VAR_TYPE::QUAT);
				value = Variable(dquat(1, 0, 0, 0));

				auto input_w = new GUI::Double_Input();
				input_w->setFixedSize(100, 20);
				input_w->setText("1");
				QObject::connect(input_w, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(val.toDouble(), original.x, original.y, original.z)); });

				PROXY(input_w);
				proxy_input_w->setPos(20, 30);

				auto input_x = new GUI::Double_Input();
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, val.toDouble(), original.y, original.z)); });

				PROXY(input_x);
				proxy_input_x->setPos(20, 50);

				auto input_y = new GUI::Double_Input();
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, original.x, val.toDouble(), original.z)); });

				PROXY(input_y);
				proxy_input_y->setPos(20, 70);

				auto input_z = new GUI::Double_Input();
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, original.x, original.y, val.toDouble())); });

				PROXY(input_z);
				proxy_input_z->setPos(20, 90);

				proxies.push(proxy_input_w);
				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 10: {
				rect.setHeight(100);
				proxy_enums->setPos(20, 70);

				out->setType(VAR_TYPE::MAT2);
				value = Variable(dmat2(1.0));

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(50, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(dvec2(val.toDouble(), original[0][1]), original[1])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(50, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(dvec2(original[0][0], val.toDouble()), original[1])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
				}
				{
					auto input_yx = new GUI::Double_Input();
					input_yx->setFixedSize(50, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(original[0], dvec2(val.toDouble(), original[0][1]))); });

					PROXY(input_yx);
					proxy_input_yx->setPos(70, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(50, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(original[0], dvec2(original[0][0], val.toDouble()))); });

					PROXY(input_yy);
					proxy_input_yy->setPos(70, 50);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
				}
				break;
			}
			case 11: {
				rect.setWidth(160);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(120);
				proxy_enums->setPos(20, 90);

				out->setType(VAR_TYPE::MAT3);
				value = Variable(dmat3(1.0));

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(val.toDouble(), original[0][1], original[0][2]), original[1], original[2])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(original[0][0], val.toDouble(), original[0][2]), original[1], original[2])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Double_Input();
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(original[0][0], original[0][1], val.toDouble()), original[1], original[2])); });

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
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(val.toDouble(), original[0][1], original[0][2]), original[2])); });

					PROXY(input_yx);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(original[0][0], val.toDouble(), original[0][2]), original[2])); });

					PROXY(input_yy);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Double_Input();
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(original[0][0], original[0][1], val.toDouble()), original[2])); });

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
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(val.toDouble(), original[0][1], original[0][2]))); });

					PROXY(input_zx);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Double_Input();
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(original[0][0], val.toDouble(), original[0][2]))); });

					PROXY(input_zy);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Double_Input();
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(original[0][0], original[0][1], val.toDouble()))); });

					PROXY(input_zz);
					proxy_input_zz->setPos(100, 70);

					proxies.push(proxy_input_zx);
					proxies.push(proxy_input_zy);
					proxies.push(proxy_input_zz);
				}
				break;
			}
			case 12: {
				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VAR_TYPE::MAT4);
				value = Variable(dmat4(1.0));

				{
					auto input_xx = new GUI::Double_Input();
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xx);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Double_Input();
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xy);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Double_Input();
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[1], original[2], original[3])); });

					PROXY(input_xz);
					proxy_input_xz->setPos(20, 70);

					auto input_xw = new GUI::Double_Input();
					input_xw->setFixedSize(40, 20);
					input_xw->setText("0");
					QObject::connect(input_xx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[1], original[2], original[3])); });

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
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[2], original[3])); });

					PROXY(input_yx);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Double_Input();
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[2], original[3])); });

					PROXY(input_yy);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Double_Input();
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[2], original[3])); });

					PROXY(input_yz);
					proxy_input_yz->setPos(60, 70);

					auto input_yw = new GUI::Double_Input();
					input_yw->setFixedSize(40, 20);
					input_yw->setText("0");
					QObject::connect(input_yx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[2], original[3])); });

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
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[3])); });

					PROXY(input_zx);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Double_Input();
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[3])); });

					PROXY(input_zy);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Double_Input();
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[3])); });

					PROXY(input_zz);
					proxy_input_zz->setPos(100, 70);

					auto input_zw = new GUI::Double_Input();
					input_zw->setFixedSize(40, 20);
					input_zw->setText("0");
					QObject::connect(input_zx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[3])); });

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
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]))); });

					PROXY(input_wx);
					proxy_input_wx->setPos(140, 30);

					auto input_wy = new GUI::Double_Input();
					input_wy->setFixedSize(40, 20);
					input_wy->setText("0");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]))); });

					PROXY(input_wy);
					proxy_input_wy->setPos(140, 50);

					auto input_wz = new GUI::Double_Input();
					input_wz->setFixedSize(40, 20);
					input_wz->setText("0");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]))); });

					PROXY(input_wz);
					proxy_input_wz->setPos(140, 70);

					auto input_ww = new GUI::Double_Input();
					input_ww->setFixedSize(40, 20);
					input_ww->setText("1");
					QObject::connect(input_wx, &GUI::Double_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()))); });

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
	});
}

Variable NODES::VARIABLES::Constant::getData(const Port* port) const {
	return value;
}

NODES::VARIABLES::Get::Get() :
	Node("Get Var")
{
	rect.setWidth(100);
	rect.setHeight(60);

	out = DATA_O("", VAR_TYPE::INT);
}

Variable NODES::VARIABLES::Get::getData(const Port* port) const {
	return SESSION->variables[var];
}

NODES::VARIABLES::Set::Set() :
	Node("Set Var")
{
	rect.setWidth(100);
	rect.setHeight(80);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");
	in  = DATA_I("", VAR_TYPE::NONE);
	out = DATA_O("", VAR_TYPE::NONE);
}

void NODES::VARIABLES::Set::exec(const Port* port) {
	SESSION->variables[var] = in->getData();
	exec_out->exec();
}

Variable NODES::VARIABLES::Set::getData(const Port* port) const {
	return SESSION->variables[var];
}

NODES::CAST::MAKE::Vec2::Vec2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_x = DATA_I("X", Variable(0.0));
	i_y = DATA_I("Y", Variable(0.0));
	out = DATA_O("", VAR_TYPE::VEC2);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	out->rect.moveCenter(QPointF(30, 20));
}

void NODES::CAST::MAKE::Vec2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec2::getData(const Port* port) const {
	return Variable(dvec2(i_x->GET_DATA(dvec1), i_y->GET_DATA(dvec1)));
}

NODES::CAST::MAKE::Vec3::Vec3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_x = DATA_I("X", Variable(0.0));
	i_y = DATA_I("Y", Variable(0.0));
	i_z = DATA_I("Z", Variable(0.0));
	out = DATA_O("", VAR_TYPE::VEC3);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	i_z->rect.moveCenter(QPointF( 0, 50));
	out->rect.moveCenter(QPointF(30, 30));
}

void NODES::CAST::MAKE::Vec3::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec3::getData(const Port* port) const {
	return Variable(dvec3(i_x->GET_DATA(dvec1), i_y->GET_DATA(dvec1), i_z->GET_DATA(dvec1)));
}

NODES::CAST::MAKE::Vec4::Vec4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_x = DATA_I("X", Variable(0.0));
	i_y = DATA_I("Y", Variable(0.0));
	i_z = DATA_I("Z", Variable(0.0));
	i_w = DATA_I("W", Variable(0.0));
	out = DATA_O("", VAR_TYPE::VEC4);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	i_z->rect.moveCenter(QPointF( 0, 50));
	i_w->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Vec4::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec4::getData(const Port* port) const {
	return Variable(dvec4(i_x->GET_DATA(dvec1), i_y->GET_DATA(dvec1), i_z->GET_DATA(dvec1), i_w->GET_DATA(dvec1)));
}

NODES::CAST::MAKE::Quat::Quat() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_w = DATA_I("W", VAR_TYPE::DOUBLE);
	i_x = DATA_I("X", VAR_TYPE::DOUBLE);
	i_y = DATA_I("Y", VAR_TYPE::DOUBLE);
	i_z = DATA_I("Z", VAR_TYPE::DOUBLE);
	out = DATA_O("", VAR_TYPE::QUAT);
	i_w->rect.moveCenter(QPointF( 0, 10));
	i_x->rect.moveCenter(QPointF( 0, 30));
	i_y->rect.moveCenter(QPointF( 0, 50));
	i_z->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Quat::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Quat::getData(const Port* port) const {
	return Variable(dquat(i_w->GET_DATA(dvec1), i_x->GET_DATA(dvec1), i_y->GET_DATA(dvec1), i_z->GET_DATA(dvec1)));
}

NODES::CAST::MAKE::Mat2::Mat2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_a = DATA_I("A", Variable(dvec2(0.0)));
	i_b = DATA_I("B", Variable(dvec2(0.0)));
	out = DATA_O("", VAR_TYPE::MAT2);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	out->rect.moveCenter(QPointF(30, 20));
}

void NODES::CAST::MAKE::Mat2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat2::getData(const Port* port) const {
	return Variable(dmat2(i_a->GET_DATA(dvec2), i_b->GET_DATA(dvec2)));
}

NODES::CAST::MAKE::Mat3::Mat3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_a = DATA_I("A", Variable(dvec3(0.0)));
	i_b = DATA_I("B", Variable(dvec3(0.0)));
	i_c = DATA_I("C", Variable(dvec3(0.0)));
	out = DATA_O("", VAR_TYPE::MAT3);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	i_c->rect.moveCenter(QPointF( 0, 50));
	out->rect.moveCenter(QPointF(30, 30));
}

void NODES::CAST::MAKE::Mat3::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat3::getData(const Port* port) const {
	return Variable(dmat3(i_a->GET_DATA(dvec3), i_b->GET_DATA(dvec3), i_c->GET_DATA(dvec3)));
}

NODES::CAST::MAKE::Mat4::Mat4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_a = DATA_I("A", Variable(dvec4(0.0)));
	i_b = DATA_I("B", Variable(dvec4(0.0)));
	i_c = DATA_I("C", Variable(dvec4(0.0)));
	i_d = DATA_I("D", Variable(dvec4(0.0)));
	out = DATA_O("", VAR_TYPE::MAT4);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	i_c->rect.moveCenter(QPointF( 0, 50));
	i_d->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Mat4::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat4::getData(const Port* port) const {
	return Variable(dmat4(i_a->GET_DATA(dvec4), i_b->GET_DATA(dvec4), i_c->GET_DATA(dvec4), i_d->GET_DATA(dvec4)));
}

NODES::Arithmetic::Arithmetic() :
	Node("Arithmetic")
{
	rect.setWidth(120);
	rect.setHeight(80);

	i_a = DATA_I("A", Variable(0.0));
	i_b = DATA_I("B", Variable(0.0));
	out = DATA_O("", VAR_TYPE::DOUBLE);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(80, 20);
	enums->addItems({ "A+B", "A-B", "A*B", "A/B" });

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

Variable NODES::Arithmetic::getData(const Port* port) const {
	switch (enums->currentIndex()) {
	case 0: return Variable(i_a->GET_DATA(dvec1) + i_b->GET_DATA(dvec1));
	case 1: return Variable(i_a->GET_DATA(dvec1) - i_b->GET_DATA(dvec1));
	case 2: return Variable(i_a->GET_DATA(dvec1) * i_b->GET_DATA(dvec1));
	case 3: return Variable(i_a->GET_DATA(dvec1) / i_b->GET_DATA(dvec1));
	}
	return Variable(0.0);
}

NODES::Trigonometry::Trigonometry() :
	Node("Trigonometry")
{
	rect.setWidth(140);
	rect.setHeight(60);

	in = DATA_I("", VAR_TYPE::DOUBLE);
	out = DATA_O("", VAR_TYPE::DOUBLE);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(100, 20);
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });

	PROXY(enums);
	proxy_enums->setPos(20, 30);
}

Variable NODES::Trigonometry::getData(const Port* port) const {
	const dvec1 x = in->GET_DATA(dvec1);
	switch (enums->currentIndex()) {
		case  0: return sin(x);
		case  1: return cos(x);
		case  2: return tan(x);
		case  3: return asin(x);
		case  4: return acos(x);
		case  5: return atan(x);
		case  6: return sinh(x);
		case  7: return cosh(x);
		case  8: return tanh(x);
		case  9: return 1.0 / tan(x);
		case 10: return 1.0 / cos(x);
		case 11: return 1.0 / sin(x);
		case 12: return cosh(x) / sinh(x);
		case 13: return 1.0 / cosh(x);
		case 14: return 1.0 / sinh(x);
	}
	return Variable(x);
}

NODES::BOOLEAN::Compare::Compare() :
	Node("Compare")
{
	rect.setWidth(120);
	rect.setHeight(80);

	in_a = DATA_I("", VAR_TYPE::NONE);
	in_b = DATA_I("", VAR_TYPE::NONE);
	out  = DATA_O("", VAR_TYPE::BOOL);

	in_a->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_b->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_a->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_b->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_a->onTypeChanged   = [this](Port* port, const VAR_TYPE& var_type) { cascade(port, var_type); };
	in_b->onTypeChanged   = [this](Port* port, const VAR_TYPE& var_type) { cascade(port, var_type); };

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "==", "!=", ">", "<", ">=", "<=", "Sign"});

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

bool NODES::BOOLEAN::Compare::onConnRequested(Port* port, Connection* conn) {
	if (port == out) {
		return true;
	}

	const VAR_TYPE incoming_type = conn->getDataO()->var_type;
	if (port == in_a) {
		if (!in_b->connected()) {
			in_a->setType(incoming_type);
			in_b->setType(incoming_type);
			return true;
		}
		else if (in_b->var_type == incoming_type) {
			in_a->setType(incoming_type);
			return true;
		}
	}
	if (port == in_b) {
		if (!in_a->connected()) {
			in_a->setType(incoming_type);
			in_b->setType(incoming_type);
			return true;
		}
		else if (in_a->var_type == incoming_type) {
			in_b->setType(incoming_type);
			return true;
		}
	}

	return false;
}

void NODES::BOOLEAN::Compare::onDisconnection(Port* port) {
	if (!in_a->connected() and !in_b->connected()) {
		in_a->setType(VAR_TYPE::NONE);
		in_b->setType(VAR_TYPE::NONE);
	}
}

void NODES::BOOLEAN::Compare::cascade(Port* port, const VAR_TYPE& var_type) {}

Variable NODES::BOOLEAN::Compare::getData(const Port* port) const {
	switch (enums->currentIndex()) {
		case 0: return Variable(in_a->getData() == in_b->getData());
		case 1: return Variable(in_a->getData() != in_b->getData());
		case 2: return Variable(in_a->getData()  > in_b->getData());
		case 3: return Variable(in_a->getData()  < in_b->getData());
		case 4: return Variable(in_a->getData() >= in_b->getData());
		case 5: return Variable(in_a->getData() <= in_b->getData());
	}
	return Variable(false);
}

NODES::BOOLEAN::If::If() :
	Node("If")
{
	rect.setWidth(40);
	rect.setHeight(80);

	in = EXEC_I("");
	condition = DATA_I("", Variable(false));
	out = EXEC_O("");
}

void NODES::BOOLEAN::If::exec(const Port* port) {
	if (condition->GET_DATA(bool)) {
		out ->exec();
	}
}

NODES::BOOLEAN::If_Else::If_Else() :
	Node("If Else")
{
	rect.setWidth(100);
	rect.setHeight(80);

	in = EXEC_I("");
	condition = DATA_I("", Variable(false));
	out_a = EXEC_O("True");
	out_b = EXEC_O("False");
}

void NODES::BOOLEAN::If_Else::exec(const Port* port) {
	if (condition->GET_DATA(bool)) {
		out_a->exec();
	}
	else {
		out_b->exec();
	}
}

NODES::BOOLEAN::Select::Select() :
	Node("Select")
{
	rect.setWidth(80);
	rect.setHeight(100);

	condition  = DATA_I("", Variable(false));
	i_true     = DATA_I("True", VAR_TYPE::NONE);
	i_false    = DATA_I("False", VAR_TYPE::NONE);
	out        = DATA_O("", VAR_TYPE::NONE);

	i_true ->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_false->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	out    ->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_true ->onDisconnection = [this](Port* port){ onDisconnection(port); };
	i_false->onDisconnection = [this](Port* port){ onDisconnection(port); };
	out    ->onDisconnection = [this](Port* port){ onDisconnection(port); };
}

bool NODES::BOOLEAN::Select::onConnRequested(Port* port, Connection* conn) {
	return false; // TODO set default var if no connection
}

void NODES::BOOLEAN::Select::onDisconnection(Port * port) {
	// TODO unset defaults
}

Variable NODES::BOOLEAN::Select::getData(const Port* port) const {
	if (condition->GET_DATA(bool)) {
		return i_true->getData();
	}
	return i_false->getData();
}

NODES::EXEC::Input_Key::Input_Key() :
	Node("Input Key")
{
	rect.setWidth(120);
	rect.setHeight(100);

	exec_press   = EXEC_O("Pressed");
	exec_release = EXEC_O("Released");
	key = DATA_O("Key", VAR_TYPE::STRING);
}

Variable NODES::EXEC::Input_Key::getData(const Port* port) const {
	return Variable("");
}

NODES::EXEC::Input_Mouse::Input_Mouse() :
	Node("Input Mouse")
{
	rect.setWidth(120);
	rect.setHeight(100);

	exec_press   = EXEC_O("Pressed");
	exec_release = EXEC_O("Released");
	button = DATA_O("Button", VAR_TYPE::STRING);
}

Variable NODES::EXEC::Input_Mouse::getData(const Port* port) const {
	return Variable("");
}

NODES::SINGLETON::Euler_Tick::Euler_Tick() :
	Node("Tick")
{
	rect.setWidth(100);
	rect.setHeight(120);

	exec_out  = EXEC_O("Tick");
	o_delta   = DATA_O("Delta", VAR_TYPE::DOUBLE);
	o_calls   = DATA_O("Calls", VAR_TYPE::INT);
	o_runtime = DATA_O("Runtime", VAR_TYPE::DOUBLE);

	delta = 0;
}

void NODES::SINGLETON::Euler_Tick::exec(const dvec1& _delta) {
	delta = _delta;
	exec_out->exec();
}

Variable NODES::SINGLETON::Euler_Tick::getData(const Port* port) const {
	if (port == o_delta)
		return Variable(delta);
	if (port == o_calls)
		return Variable(SESSION->current_frame);
	if (port == o_runtime)
		return Variable(chrono::duration<double>(NOW - SESSION->start).count());
}

NODES::SINGLETON::Background::Background() :
	Node("Background")
{
	rect.setWidth(120);
	rect.setHeight(80);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	color_in = DATA_I("Color", Variable(Color()));
}

void NODES::SINGLETON::Background::exec(const Port* port) {
	const vec4 u_color = d_to_f(color_in->GET_DATA(Color).rgba());
	GL->glClearColor(u_color.r, u_color.g, u_color.b, u_color.a);
	GL->glClear(GL_COLOR_BUFFER_BIT);
	exec_out->exec();
}

NODES::SINGLETON::Camera_2D::Camera_2D() :
	Node("2D Camera")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(100);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	center = DATA_I("Color", Variable(dvec2(0,0)));
	zoom = DATA_I("Color", Variable(1.0));
}

void NODES::SINGLETON::Camera_2D::exec(const Port* port) {
	SESSION->viewport->center_2d = center->GET_DATA(dvec2);
	SESSION->viewport->zoom_2d = zoom->GET_DATA(dvec1);
	exec_out->exec();
}

NODES::SINGLETON::Camera_3D::Camera_3D() :
	Node("3D Camera")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(100);
	rect.setHeight(60);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");
}

void NODES::SINGLETON::Camera_3D::exec(const Port* port) {
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Line::Line() :
	Node("Line")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(dvec2(-200, -200)));
	vert_b = DATA_I("B", Variable(dvec2( 200,  200)));
	width  = DATA_I("Width", Variable(3.0));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Line::render() {
	// Update vertices
	const auto v1      = d_to_f(vert_a->GET_DATA(dvec2));
	const auto v2      = d_to_f(vert_b->GET_DATA(dvec2));
	const auto radius  = d_to_f(width ->GET_DATA(dvec1));
	const auto u_color = color->GET_DATA(Color);

	RENDER::Dim_2D::Line(v1, v2, radius, u_color);
}

void NODES::RENDERING::DIM_2D::Line::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Triangle::Triangle() :
	Node("Tri")
{
	VAO, VBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(dvec2(  0,  57.777)));
	vert_b = DATA_I("B", Variable(dvec2(-50, -28.868)));
	vert_c = DATA_I("C", Variable(dvec2( 50, -28.868)));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));

	init();
}

void NODES::RENDERING::DIM_2D::Triangle::init() {
	const GLfloat vertices[6] = { 0 };
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Triangle::render() {
	// Update vertices
	const auto v1      = d_to_f(vert_a->GET_DATA(dvec2));
	const auto v2      = d_to_f(vert_b->GET_DATA(dvec2));
	const auto v3      = d_to_f(vert_c->GET_DATA(dvec2));
	const auto u_color = color ->GET_DATA(Color).fRgba();

	const GLfloat vertices[6] = {
		v1.x, v1.y,
		v2.x, v2.y,
		v3.x, v3.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION->viewport->SP_2D_Triangle;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION->viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION->viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION->viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(u_color));

	GL->glBindVertexArray(VAO);
	GL->glDrawArrays(GL_TRIANGLES, 0, 3);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Triangle::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Rectangle::Rectangle() :
	Node("Rect")
{
	VAO, VBO, EBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(160);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(dvec2(-100, -100)));
	vert_b = DATA_I("B", Variable(dvec2(-100,  100)));
	vert_c = DATA_I("C", Variable(dvec2( 100,  100)));
	vert_d = DATA_I("D", Variable(dvec2( 100, -100)));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));

	init();
}

void NODES::RENDERING::DIM_2D::Rectangle::init() {
	const GLfloat vertices[8] = { 0 };
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);
	GL->glGenBuffers(1, &EBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Rectangle::render() {
	// Update vertices
	const auto v1      = d_to_f(vert_a->GET_DATA(dvec2));
	const auto v2      = d_to_f(vert_b->GET_DATA(dvec2));
	const auto v3      = d_to_f(vert_c->GET_DATA(dvec2));
	const auto v4      = d_to_f(vert_d->GET_DATA(dvec2));
	const auto u_color = color ->GET_DATA(Color).fRgba();

	const GLfloat vertices[8] = {
		v1.x, v1.y,
		v2.x, v2.y,
		v3.x, v3.y,
		v4.x, v4.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION->viewport->SP_2D_Rectangle;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION->viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION->viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION->viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(u_color));

	GL->glBindVertexArray(VAO);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Rectangle::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Circle::Circle() :
	Node("Circle")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(120);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	center = DATA_I("Center", Variable(dvec2(0, 0)));
	radius = DATA_I("Radius", Variable(50.0));
	color  = DATA_I("Color" , Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Circle::render() {
	const auto u_center = d_to_f(center->GET_DATA(dvec2));
	const auto u_radius = d_to_f(radius->GET_DATA(dvec1));
	const auto u_color  = color->GET_DATA(Color);

	RENDER::Dim_2D::Circle(u_center, u_radius, u_color);
}

void NODES::RENDERING::DIM_2D::Circle::exec(const Port* port) {
	render();
	exec_out->exec();
}