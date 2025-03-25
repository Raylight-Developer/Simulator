#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

NODES::VARIABLES::Constant::Constant() :
	Node("Constant")
{
	rect.setWidth(140);
	rect.setHeight(60);

	out = new PORT::Data_O(this, "", VARIABLE::Type::BLOCKED);
	value = Variable();

	enums = new GUI::Options();
	enums->setFixedSize(100, 20);
	enums->addItems({ "", "Integer", "Double", "Bool", "String", "Vec2", "Vec3", "Vec4", "Quat", "Mat2", "Mat3", "Mat4" });

	auto* proxy_enums = new GUI::Graphics_Widget(enums, this);
	proxy_enums->setPos(20, 30);

	out->onConnRequested = [this, proxy_enums](Port* port, Connection* conn) {
		rect.setHeight(rect.height() - 20);
		proxy_enums->setVisible(false);
		return true;
	};
	out->onDisconnection = [this, proxy_enums](Port* port) {
		rect.setHeight(rect.height() + 20);
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
				out->setType(VARIABLE::Type::BLOCKED);
				value = Variable();
				break;
			}
			case 1: {
				out->setType(VARIABLE::Type::INT);
				value = Variable(0LL);

				auto input = new GUI::Value_Input();
				input->setValidator(new QIntValidator(input));
				input->setFixedSize(100, 20);
				input->setText("0");
				QObject::connect(input, &GUI::Value_Input::textChanged, [this](const QString val) { value = Variable(i_to_il(val.toInt())); });

				auto* proxy_input = new GUI::Graphics_Widget(input, this);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 2: {
				out->setType(VARIABLE::Type::DOUBLE);
				value = Variable(0.0);

				auto input = new GUI::Value_Input();
				input->setValidator(new QDoubleValidator(input));
				input->setFixedSize(100, 20);
				input->setText("0");
				QObject::connect(input, &GUI::Value_Input::textChanged, [this](const QString val) { value = Variable(val.toDouble()); });

				auto* proxy_input = new GUI::Graphics_Widget(input, this);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 3: {
				out->setType(VARIABLE::Type::BOOL);
				value = Variable(false);

				auto input = new GUI::Toggle();
				input->setFixedSize(20, 20);

				QObject::connect(input, &GUI::Toggle::toggled, [this](bool checked) { value = Variable(checked); });

				auto* proxy_input = new GUI::Graphics_Widget(input, this);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 4: {
				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));

				out->setType(VARIABLE::Type::STRING);
				value = Variable(0.0);

				auto input = new GUI::Value_Input();
				input->setFixedSize(160, 20);
				input->setPlaceholderText("String");
				input->setText("");
				QObject::connect(input, &GUI::Value_Input::textChanged, [this](const QString val) { value = Variable(val); });

				auto* proxy_input = new GUI::Graphics_Widget(input, this);
				proxy_input->setPos(20, 30);

				proxies.push(proxy_input);
				break;
			}
			case 5: {
				rect.setHeight(100);
				proxy_enums->setPos(20, 70);

				out->setType(VARIABLE::Type::VEC2);
				value = Variable(dvec2(0.0));

				auto input_x = new GUI::Value_Input();
				input_x->setValidator(new QDoubleValidator(input_x));
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec2>(); value = Variable(dvec2(val.toDouble(), original.y)); });

				auto* proxy_input_x = new GUI::Graphics_Widget(input_x, this);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Value_Input();
				input_y->setValidator(new QDoubleValidator(input_y));
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec2>(); value = Variable(dvec2(original.x, val.toDouble())); });

				auto* proxy_input_y = new GUI::Graphics_Widget(input_y, this);
				proxy_input_y->setPos(20, 50);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				break;
			}
			case 6: {
				rect.setHeight(120);
				proxy_enums->setPos(20, 90);

				out->setType(VARIABLE::Type::VEC3);
				value = Variable(dvec3(0.0));

				auto input_x = new GUI::Value_Input();
				input_x->setValidator(new QDoubleValidator(input_x));
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(val.toDouble(), original.y, original.z)); });

				auto* proxy_input_x = new GUI::Graphics_Widget(input_x, this);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Value_Input();
				input_y->setValidator(new QDoubleValidator(input_y));
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(original.x, val.toDouble(), original.z)); });

				auto* proxy_input_y = new GUI::Graphics_Widget(input_y, this);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Value_Input();
				input_z->setValidator(new QDoubleValidator(input_z));
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec3>(); value = Variable(dvec3(original.x, original.y, val.toDouble())); });

				auto* proxy_input_z = new GUI::Graphics_Widget(input_z, this);
				proxy_input_z->setPos(20, 70);

				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 7: {
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VARIABLE::Type::VEC4);
				value = Variable(dvec4(0.0));

				auto input_x = new GUI::Value_Input();
				input_x->setValidator(new QDoubleValidator(input_x));
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(val.toDouble(), original.y, original.z, original.w)); });

				auto* proxy_input_x = new GUI::Graphics_Widget(input_x, this);
				proxy_input_x->setPos(20, 30);

				auto input_y = new GUI::Value_Input();
				input_y->setValidator(new QDoubleValidator(input_y));
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, val.toDouble(), original.z, original.w)); });

				auto* proxy_input_y = new GUI::Graphics_Widget(input_y, this);
				proxy_input_y->setPos(20, 50);

				auto input_z = new GUI::Value_Input();
				input_z->setValidator(new QDoubleValidator(input_z));
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, original.y, val.toDouble(), original.z)); });

				auto* proxy_input_z = new GUI::Graphics_Widget(input_z, this);
				proxy_input_z->setPos(20, 70);

				auto input_w = new GUI::Value_Input();
				input_w->setValidator(new QDoubleValidator(input_w));
				input_w->setFixedSize(100, 20);
				input_w->setText("0");
				QObject::connect(input_w, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dvec4(original.x, original.y, original.z, val.toDouble())); });

				auto* proxy_input_w = new GUI::Graphics_Widget(input_w, this);
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

				out->setType(VARIABLE::Type::QUAT);
				value = Variable(dquat(1, 0, 0, 0));

				auto input_w = new GUI::Value_Input();
				input_w->setValidator(new QDoubleValidator(input_w));
				input_w->setFixedSize(100, 20);
				input_w->setText("1");
				QObject::connect(input_w, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(val.toDouble(), original.x, original.y, original.z)); });

				auto* proxy_input_w = new GUI::Graphics_Widget(input_w, this);
				proxy_input_w->setPos(20, 30);

				auto input_x = new GUI::Value_Input();
				input_x->setValidator(new QDoubleValidator(input_x));
				input_x->setFixedSize(100, 20);
				input_x->setText("0");
				QObject::connect(input_x, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, val.toDouble(), original.y, original.z)); });

				auto* proxy_input_x = new GUI::Graphics_Widget(input_x, this);
				proxy_input_x->setPos(20, 50);

				auto input_y = new GUI::Value_Input();
				input_y->setValidator(new QDoubleValidator(input_y));
				input_y->setFixedSize(100, 20);
				input_y->setText("0");
				QObject::connect(input_y, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, original.x, val.toDouble(), original.z)); });

				auto* proxy_input_y = new GUI::Graphics_Widget(input_y, this);
				proxy_input_y->setPos(20, 70);

				auto input_z = new GUI::Value_Input();
				input_z->setValidator(new QDoubleValidator(input_z));
				input_z->setFixedSize(100, 20);
				input_z->setText("0");
				QObject::connect(input_z, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dvec4>(); value = Variable(dquat(original.w, original.x, original.y, val.toDouble())); });

				auto* proxy_input_z = new GUI::Graphics_Widget(input_z, this);
				proxy_input_z->setPos(20, 90);

				proxies.push(proxy_input_w);
				proxies.push(proxy_input_x);
				proxies.push(proxy_input_y);
				proxies.push(proxy_input_z);
				break;
			}
			case 9: {
				rect.setWidth(140);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(100);
				proxy_enums->setPos(20, 70);

				out->setType(VARIABLE::Type::MAT2);
				value = Variable(dmat2(1.0));

				{
					auto input_xx = new GUI::Value_Input();
					input_xx->setValidator(new QDoubleValidator(input_xx));
					input_xx->setFixedSize(50, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(dvec2(val.toDouble(), original[0][1]), original[1])); });

					auto* proxy_input_xx = new GUI::Graphics_Widget(input_xx, this);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Value_Input();
					input_xy->setValidator(new QDoubleValidator(input_xy));
					input_xy->setFixedSize(50, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(dvec2(original[0][0], val.toDouble()), original[1])); });

					auto* proxy_input_xy = new GUI::Graphics_Widget(input_xy, this);
					proxy_input_xy->setPos(20, 50);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
				}
				{
					auto input_yx = new GUI::Value_Input();
					input_yx->setValidator(new QDoubleValidator(input_yx));
					input_yx->setFixedSize(50, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(original[0], dvec2(val.toDouble(), original[0][1]))); });

					auto* proxy_input_yx = new GUI::Graphics_Widget(input_yx, this);
					proxy_input_yx->setPos(70, 30);

					auto input_yy = new GUI::Value_Input();
					input_yy->setValidator(new QDoubleValidator(input_yy));
					input_yy->setFixedSize(50, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat2>(); value = Variable(dmat2(original[0], dvec2(original[0][0], val.toDouble()))); });

					auto* proxy_input_yy = new GUI::Graphics_Widget(input_yy, this);
					proxy_input_yy->setPos(70, 50);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
				}
				break;
			}
			case 10: {
				rect.setWidth(160);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(120);
				proxy_enums->setPos(20, 90);

				out->setType(VARIABLE::Type::MAT3);
				value = Variable(dmat3(1.0));

				{
					auto input_xx = new GUI::Value_Input();
					input_xx->setValidator(new QDoubleValidator(input_xx));
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(val.toDouble(), original[0][1], original[0][2]), original[1], original[2])); });

					auto* proxy_input_xx = new GUI::Graphics_Widget(input_xx, this);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Value_Input();
					input_xy->setValidator(new QDoubleValidator(input_xy));
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(original[0][0], val.toDouble(), original[0][2]), original[1], original[2])); });

					auto* proxy_input_xy = new GUI::Graphics_Widget(input_xy, this);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Value_Input();
					input_xz->setValidator(new QDoubleValidator(input_xz));
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(dvec3(original[0][0], original[0][1], val.toDouble()), original[1], original[2])); });

					auto* proxy_input_xz = new GUI::Graphics_Widget(input_xz, this);
					proxy_input_xz->setPos(20, 70);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
					proxies.push(proxy_input_xz);
				}
				{
					auto input_yx = new GUI::Value_Input();
					input_yx->setValidator(new QDoubleValidator(input_yx));
					input_yx->setFixedSize(40, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(val.toDouble(), original[0][1], original[0][2]), original[2])); });

					auto* proxy_input_yx = new GUI::Graphics_Widget(input_yx, this);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Value_Input();
					input_yy->setValidator(new QDoubleValidator(input_yy));
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(original[0][0], val.toDouble(), original[0][2]), original[2])); });

					auto* proxy_input_yy = new GUI::Graphics_Widget(input_yy, this);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Value_Input();
					input_yz->setValidator(new QDoubleValidator(input_yz));
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], dvec3(original[0][0], original[0][1], val.toDouble()), original[2])); });

					auto* proxy_input_yz = new GUI::Graphics_Widget(input_yz, this);
					proxy_input_yz->setPos(60, 70);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
					proxies.push(proxy_input_yz);
				}
				{
					auto input_zx = new GUI::Value_Input();
					input_zx->setValidator(new QDoubleValidator(input_zx));
					input_zx->setFixedSize(40, 20);
					input_zx->setText("0");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(val.toDouble(), original[0][1], original[0][2]))); });

					auto* proxy_input_zx = new GUI::Graphics_Widget(input_zx, this);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Value_Input();
					input_zy->setValidator(new QDoubleValidator(input_zy));
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(original[0][0], val.toDouble(), original[0][2]))); });

					auto* proxy_input_zy = new GUI::Graphics_Widget(input_zy, this);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Value_Input();
					input_zz->setValidator(new QDoubleValidator(input_zz));
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat3>(); value = Variable(dmat3(original[0], original[1], dvec3(original[0][0], original[0][1], val.toDouble()))); });

					auto* proxy_input_zz = new GUI::Graphics_Widget(input_zz, this);
					proxy_input_zz->setPos(100, 70);

					proxies.push(proxy_input_zx);
					proxies.push(proxy_input_zy);
					proxies.push(proxy_input_zz);
				}
				break;
			}
			case 11: {
				rect.setWidth(200);
				out->rect.moveCenter(rect.topRight() + QPointF(0, 40));
				rect.setHeight(140);
				proxy_enums->setPos(20, 110);

				out->setType(VARIABLE::Type::MAT4);
				value = Variable(dmat4(1.0));

				{
					auto input_xx = new GUI::Value_Input();
					input_xx->setValidator(new QDoubleValidator(input_xx));
					input_xx->setFixedSize(40, 20);
					input_xx->setText("1");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[1], original[2], original[3])); });

					auto* proxy_input_xx = new GUI::Graphics_Widget(input_xx, this);
					proxy_input_xx->setPos(20, 30);

					auto input_xy = new GUI::Value_Input();
					input_xy->setValidator(new QDoubleValidator(input_xy));
					input_xy->setFixedSize(40, 20);
					input_xy->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[1], original[2], original[3])); });

					auto* proxy_input_xy = new GUI::Graphics_Widget(input_xy, this);
					proxy_input_xy->setPos(20, 50);

					auto input_xz = new GUI::Value_Input();
					input_xz->setValidator(new QDoubleValidator(input_xz));
					input_xz->setFixedSize(40, 20);
					input_xz->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[1], original[2], original[3])); });

					auto* proxy_input_xz = new GUI::Graphics_Widget(input_xz, this);
					proxy_input_xz->setPos(20, 70);

					auto input_xw = new GUI::Value_Input();
					input_xw->setValidator(new QDoubleValidator(input_xw));
					input_xw->setFixedSize(40, 20);
					input_xw->setText("0");
					QObject::connect(input_xx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[1], original[2], original[3])); });

					auto* proxy_input_xw = new GUI::Graphics_Widget(input_xw, this);
					proxy_input_xw->setPos(20, 90);

					proxies.push(proxy_input_xx);
					proxies.push(proxy_input_xy);
					proxies.push(proxy_input_xz);
					proxies.push(proxy_input_xw);
				}
				{
					auto input_yx = new GUI::Value_Input();
					input_yx->setValidator(new QDoubleValidator(input_yx));
					input_yx->setFixedSize(40, 20);
					input_yx->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[2], original[3])); });

					auto* proxy_input_yx = new GUI::Graphics_Widget(input_yx, this);
					proxy_input_yx->setPos(60, 30);

					auto input_yy = new GUI::Value_Input();
					input_yy->setValidator(new QDoubleValidator(input_yy));
					input_yy->setFixedSize(40, 20);
					input_yy->setText("1");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[2], original[3])); });

					auto* proxy_input_yy = new GUI::Graphics_Widget(input_yy, this);
					proxy_input_yy->setPos(60, 50);

					auto input_yz = new GUI::Value_Input();
					input_yz->setValidator(new QDoubleValidator(input_yz));
					input_yz->setFixedSize(40, 20);
					input_yz->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[2], original[3])); });

					auto* proxy_input_yz = new GUI::Graphics_Widget(input_yz, this);
					proxy_input_yz->setPos(60, 70);

					auto input_yw = new GUI::Value_Input();
					input_yw->setValidator(new QDoubleValidator(input_yw));
					input_yw->setFixedSize(40, 20);
					input_yw->setText("0");
					QObject::connect(input_yx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[2], original[3])); });

					auto* proxy_input_yw = new GUI::Graphics_Widget(input_yw, this);
					proxy_input_yw->setPos(60, 90);

					proxies.push(proxy_input_yx);
					proxies.push(proxy_input_yy);
					proxies.push(proxy_input_yz);
					proxies.push(proxy_input_yw);
				}
				{
					auto input_zx = new GUI::Value_Input();
					input_zx->setValidator(new QDoubleValidator(input_zx));
					input_zx->setFixedSize(40, 20);
					input_zx->setText("0");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]), original[3])); });

					auto* proxy_input_zx = new GUI::Graphics_Widget(input_zx, this);
					proxy_input_zx->setPos(100, 30);

					auto input_zy = new GUI::Value_Input();
					input_zy->setValidator(new QDoubleValidator(input_zy));
					input_zy->setFixedSize(40, 20);
					input_zy->setText("0");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]), original[3])); });

					auto* proxy_input_zy = new GUI::Graphics_Widget(input_zy, this);
					proxy_input_zy->setPos(100, 50);

					auto input_zz = new GUI::Value_Input();
					input_zz->setValidator(new QDoubleValidator(input_zz));
					input_zz->setFixedSize(40, 20);
					input_zz->setText("1");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]), original[3])); });

					auto* proxy_input_zz = new GUI::Graphics_Widget(input_zz, this);
					proxy_input_zz->setPos(100, 70);

					auto input_zw = new GUI::Value_Input();
					input_zw->setValidator(new QDoubleValidator(input_zw));
					input_zw->setFixedSize(40, 20);
					input_zw->setText("0");
					QObject::connect(input_zx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()), original[3])); });

					auto* proxy_input_zw = new GUI::Graphics_Widget(input_zw, this);
					proxy_input_zw->setPos(100, 90);

					proxies.push(proxy_input_zx);
					proxies.push(proxy_input_zy);
					proxies.push(proxy_input_zz);
					proxies.push(proxy_input_zw);
				}
				{
					auto input_wx = new GUI::Value_Input();
					input_wx->setValidator(new QDoubleValidator(input_wx));
					input_wx->setFixedSize(40, 20);
					input_wx->setText("0");
					QObject::connect(input_wx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(val.toDouble(), original[0][1], original[0][2], original[0][3]))); });

					auto* proxy_input_wx = new GUI::Graphics_Widget(input_wx, this);
					proxy_input_wx->setPos(140, 30);

					auto input_wy = new GUI::Value_Input();
					input_wy->setValidator(new QDoubleValidator(input_wy));
					input_wy->setFixedSize(40, 20);
					input_wy->setText("0");
					QObject::connect(input_wx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], val.toDouble(), original[0][2], original[0][3]))); });

					auto* proxy_input_wy = new GUI::Graphics_Widget(input_wy, this);
					proxy_input_wy->setPos(140, 50);

					auto input_wz = new GUI::Value_Input();
					input_wz->setValidator(new QDoubleValidator(input_wz));
					input_wz->setFixedSize(40, 20);
					input_wz->setText("0");
					QObject::connect(input_wx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], original[0][1], val.toDouble(), original[0][3]))); });

					auto* proxy_input_wz = new GUI::Graphics_Widget(input_wz, this);
					proxy_input_wz->setPos(140, 70);

					auto input_ww = new GUI::Value_Input();
					input_ww->setValidator(new QDoubleValidator(input_ww));
					input_ww->setFixedSize(40, 20);
					input_ww->setText("1");
					QObject::connect(input_wx, &GUI::Value_Input::textChanged, [this](const QString val) { const auto original = value.get<dmat4>(); value = Variable(dmat4(original[0], original[1], original[2], dvec4(original[0][0], original[0][1], original[0][2], val.toDouble()))); });

					auto* proxy_input_ww = new GUI::Graphics_Widget(input_ww, this);
					proxy_input_ww->setPos(140, 90);

					proxies.push(proxy_input_wx);
					proxies.push(proxy_input_wy);
					proxies.push(proxy_input_wz);
					proxies.push(proxy_input_ww);
				}
				break;
			}
		}
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

	out = new PORT::Data_O(this, "", VARIABLE::Type::INT);
}

Variable NODES::VARIABLES::Get::getData(const Port* port) const {
	return SESSION->variables[var];
}

NODES::VARIABLES::Set::Set() :
	Node("Set Var")
{
	rect.setWidth(100);
	rect.setHeight(60);

	exec_in  = new PORT::Exec_I(this, "");
	exec_out = new PORT::Exec_O(this, "");
	in  = new PORT::Data_I(this, "", VARIABLE::Type::NONE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::NONE);
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

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::DOUBLE);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::DOUBLE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC2);
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
	return Variable(dvec2(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Vec3::Vec3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::DOUBLE);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::DOUBLE);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::DOUBLE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC3);
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
	return Variable(dvec3(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Vec4::Vec4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::DOUBLE);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::DOUBLE);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::DOUBLE);
	i_w = new PORT::Data_I(this, "W", VARIABLE::Type::DOUBLE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC4);
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
	return Variable(dvec4(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>(), i_w->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Quat::Quat() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_w = new PORT::Data_I(this, "W", VARIABLE::Type::DOUBLE);
	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::DOUBLE);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::DOUBLE);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::DOUBLE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::QUAT);
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
	return Variable(dquat(i_w->getData().get<dvec1>(), i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Mat2::Mat2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC2);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC2);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT2);
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
	return Variable(dmat2(i_a->getData().get<dvec2>(), i_b->getData().get<dvec2>()));
}

NODES::CAST::MAKE::Mat3::Mat3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC3);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC3);
	i_c = new PORT::Data_I(this, "C", VARIABLE::Type::VEC3);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT3);
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
	return Variable(dmat3(i_a->getData().get<dvec3>(), i_b->getData().get<dvec3>(), i_c->getData().get<dvec3>()));
}

NODES::CAST::MAKE::Mat4::Mat4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC4);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC4);
	i_c = new PORT::Data_I(this, "C", VARIABLE::Type::VEC4);
	i_d = new PORT::Data_I(this, "D", VARIABLE::Type::VEC4);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT4);
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
	return Variable(dmat4(i_a->getData().get<dvec4>(), i_b->getData().get<dvec4>(), i_c->getData().get<dvec4>(), i_d->getData().get<dvec4>()));
}

NODES::Arithmetic::Arithmetic() :
	Node("Arithmetic")
{
	rect.setWidth(120);
	rect.setHeight(80);

	i_a = new PORT::Data_I(this, "A", Variable(0.0));
	i_b = new PORT::Data_I(this, "B", Variable(0.0));
	out = new PORT::Data_O(this, "", VARIABLE::Type::DOUBLE);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(80, 20);
	enums->addItems({ "A+B", "A-B", "A*B", "A/B" });

	auto pw_enums = new GUI::Graphics_Widget(enums, this);
	pw_enums->setPos(30, 50);
}

Variable NODES::Arithmetic::getData(const Port* port) const {
	switch (enums->currentIndex()) {
	case 0: return Variable(i_a->getData().get<dvec1>() + i_b->getData().get<dvec1>());
	case 1: return Variable(i_a->getData().get<dvec1>() - i_b->getData().get<dvec1>());
	case 2: return Variable(i_a->getData().get<dvec1>() * i_b->getData().get<dvec1>());
	case 3: return Variable(i_a->getData().get<dvec1>() / i_b->getData().get<dvec1>());
	}
	return Variable(0.0);
}

NODES::Trigonometry::Trigonometry() :
	Node("Trigonometry")
{
	rect.setWidth(140);
	rect.setHeight(60);

	in = new PORT::Data_I(this, "", VARIABLE::Type::DOUBLE);
	out = new PORT::Data_O(this, "", VARIABLE::Type::DOUBLE);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(100, 20);
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });

	auto* proxyWidget = new GUI::Graphics_Widget(enums, this);
	proxyWidget->setPos(20, 30);
}

Variable NODES::Trigonometry::getData(const Port* port) const {
	const dvec1 x = in->getData().get<dvec1>();
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

	in_a = new PORT::Data_I(this, "", VARIABLE::Type::NONE);
	in_b = new PORT::Data_I(this, "", VARIABLE::Type::NONE);
	out  = new PORT::Data_O(this, "", VARIABLE::Type::BOOL);

	in_a->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_b->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_a->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_b->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_a->onTypeChanged   = [this](Port* port, const VARIABLE::Type& var_type) { cascade(port, var_type); };
	in_b->onTypeChanged   = [this](Port* port, const VARIABLE::Type& var_type) { cascade(port, var_type); };

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "==", "!=", ">", "<", ">=", "<=", "Sign"});

	auto* proxyWidget = new GUI::Graphics_Widget(enums, this);
	proxyWidget->setPos(30, 50);
}

bool NODES::BOOLEAN::Compare::onConnRequested(Port* port, Connection* conn) {
	if (port == out) {
		return true;
	}

	const VARIABLE::Type incoming_type = conn->getDataO()->var_type;
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
		in_a->setType(VARIABLE::Type::NONE);
		in_b->setType(VARIABLE::Type::NONE);
	}
}

void NODES::BOOLEAN::Compare::cascade(Port* port, const VARIABLE::Type& var_type) {}

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

	in = new PORT::Exec_I(this, "");
	condition = new PORT::Data_I(this, "", Variable(false));
	out = new PORT::Exec_O(this, "");
}

void NODES::BOOLEAN::If::exec(const Port* port) {
	if (condition->getData().get<bool>()) {
		out ->exec();
	}
}

NODES::BOOLEAN::If_Else::If_Else() :
	Node("If Else")
{
	rect.setWidth(100);
	rect.setHeight(80);

	in = new PORT::Exec_I(this, "");
	condition = new PORT::Data_I(this, "", Variable(false));
	out_a = new PORT::Exec_O(this, "True");
	out_b = new PORT::Exec_O(this, "False");
}

void NODES::BOOLEAN::If_Else::exec(const Port* port) {
	if (condition->getData().get<bool>()) {
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

	condition  = new PORT::Data_I(this, "", Variable(false));
	i_true     = new PORT::Data_I(this, "True", VARIABLE::Type::NONE);
	i_false    = new PORT::Data_I(this, "False", VARIABLE::Type::NONE);
	out        = new PORT::Data_O(this, "", VARIABLE::Type::NONE);

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
	if (condition->getData().get<bool>()) {
		return i_true->getData();
	}
	return i_false->getData();
}

NODES::DEFAULT::Euler_Tick::Euler_Tick() :
	Node("Tick")
{
	rect.setWidth(80);
	rect.setHeight(80);

	exec_out = new PORT::Exec_O(this, "Tick");
	delta_out = new PORT::Data_O(this, "Delta", VARIABLE::Type::DOUBLE);

	delta = 0.016;
}

void NODES::DEFAULT::Euler_Tick::exec(const dvec1& delta) {
	this->delta = delta;
	exec_out->exec();
}

Variable NODES::DEFAULT::Euler_Tick::getData(const Port* port) const {
	return Variable(delta);
}

NODES::DEFAULT::Background::Background() :
	Node("Background")
{
	rect.setWidth(100);
	rect.setHeight(80);

	exec_in  = new PORT:: Exec_I(this, "");
	exec_out = new PORT:: Exec_O(this, "");

	color_in = new PORT:: Data_I(this, "Color", Variable(dvec4(0,0,0,1)));
}

void NODES::DEFAULT::Background::exec(const Port* port) {
	const vec4 u_color = d_to_f(color_in->getData().get<dvec4>());
	GL->glClearColor(u_color.r, u_color.g, u_color.b, u_color.a);
	GL->glClear(GL_COLOR_BUFFER_BIT);
	exec_out->exec();
}

NODES::DEFAULT::Camera_2D::Camera_2D() :
	Node("2D Camera")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(100);

	exec_in  = new PORT:: Exec_I(this, "");
	exec_out = new PORT:: Exec_O(this, "");

	center = new PORT:: Data_I(this, "Color", Variable(dvec2(0,0)));
	zoom = new PORT:: Data_I(this, "Color", Variable(1.0));
}

void NODES::DEFAULT::Camera_2D::exec(const Port* port) {
	SESSION->viewport->center_2d = center->getData().get<dvec2>();
	SESSION->viewport->zoom_2d = zoom->getData().get<dvec1>();
	exec_out->exec();
}

NODES::DEFAULT::Camera_3D::Camera_3D() :
	Node("3D Camera")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(100);
	rect.setHeight(60);

	exec_in  = new PORT:: Exec_I(this, "");
	exec_out = new PORT:: Exec_O(this, "");
}

void NODES::DEFAULT::Camera_3D::exec(const Port* port) {
	exec_out->exec();
}

NODES::DEFAULT::Input_Key::Input_Key() :
	Node("Input Key")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	exec_press   = new PORT:: Exec_O(this, "Pressed");
	exec_release = new PORT:: Exec_O(this, "Released");
	key = new PORT::Data_O(this, "Key", VARIABLE::Type::STRING);
}

Variable NODES::DEFAULT::Input_Key::getData(const Port* port) const {
	return Variable("");
}

NODES::DEFAULT::Input_Mouse::Input_Mouse() :
	Node("Input Mouse")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	exec_press   = new PORT:: Exec_O(this, "Pressed");
	exec_release = new PORT:: Exec_O(this, "Released");
	button = new PORT::Data_O(this, "Button", VARIABLE::Type::STRING);
}

Variable NODES::DEFAULT::Input_Mouse::getData(const Port* port) const {
	return Variable("");
}

NODES::RENDERING::DIM_2D::Line::Line() :
	Node("Line")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	exec_in  = new PORT::Exec_I(this, "");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "A", Variable(dvec2(-200, -200)));
	vert_b = new PORT::Data_I(this, "B", Variable(dvec2( 200,  200)));
	width  = new PORT::Data_I(this, "Width", Variable(3.0));
	color  = new PORT::Data_I(this, "Color", Variable(dvec4(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Line::render() {
	// Update vertices
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec1 radius  = d_to_f(width ->getData().get<dvec1>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

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

	exec_in  = new PORT::Exec_I(this, "");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "A", Variable(dvec2(  0,  57.777)));
	vert_b = new PORT::Data_I(this, "B", Variable(dvec2(-50, -28.868)));
	vert_c = new PORT::Data_I(this, "C", Variable(dvec2( 50, -28.868)));
	color  = new PORT::Data_I(this, "Color", Variable(dvec4(1, 1, 1, 1)));

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
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec2 v3      = d_to_f(vert_c->getData().get<dvec2>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

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

	exec_in  = new PORT::Exec_I(this, "");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "A", Variable(dvec2(-100, -100)));
	vert_b = new PORT::Data_I(this, "B", Variable(dvec2(-100,  100)));
	vert_c = new PORT::Data_I(this, "C", Variable(dvec2( 100,  100)));
	vert_d = new PORT::Data_I(this, "D", Variable(dvec2( 100, -100)));
	color  = new PORT::Data_I(this, "Color", Variable(dvec4(1, 1, 1, 1)));

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
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec2 v3      = d_to_f(vert_c->getData().get<dvec2>());
	const vec2 v4      = d_to_f(vert_d->getData().get<dvec2>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

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

	exec_in  = new PORT::Exec_I(this, "");
	exec_out = new PORT::Exec_O(this, "");

	center = new PORT::Data_I(this, "Center", Variable(dvec2(0, 0)));
	radius = new PORT::Data_I(this, "Radius", Variable(50.0));
	color  = new PORT::Data_I(this, "Color" , Variable(dvec4(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Circle::render() {
	const vec4 u_color  = d_to_f(color ->getData().get<dvec4>());
	const vec2 u_center = d_to_f(center->getData().get<dvec2>());
	const vec1 u_radius = d_to_f(radius->getData().get<dvec1>());

	RENDER::Dim_2D::Circle(u_center, u_radius, u_color);
}

void NODES::RENDERING::DIM_2D::Circle::exec(const Port* port) {
	render();
	exec_out->exec();
}