#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

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
	return Variable(F64_V2(i_x->GET_DATA(F64), i_y->GET_DATA(F64)));
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
	return Variable(F64_V3(i_x->GET_DATA(F64), i_y->GET_DATA(F64), i_z->GET_DATA(F64)));
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
	return Variable(F64_V4(i_x->GET_DATA(F64), i_y->GET_DATA(F64), i_z->GET_DATA(F64), i_w->GET_DATA(F64)));
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
	return Variable(F64_Quat(i_w->GET_DATA(F64), i_x->GET_DATA(F64), i_y->GET_DATA(F64), i_z->GET_DATA(F64)));
}

NODES::CAST::MAKE::Mat2::Mat2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_a = DATA_I("A", Variable(F64_V2(0.0)));
	i_b = DATA_I("B", Variable(F64_V2(0.0)));
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
	return Variable(F64_M2(i_a->GET_DATA(F64_V2), i_b->GET_DATA(F64_V2)));
}

NODES::CAST::MAKE::Mat3::Mat3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_a = DATA_I("A", Variable(F64_V3(0.0)));
	i_b = DATA_I("B", Variable(F64_V3(0.0)));
	i_c = DATA_I("C", Variable(F64_V3(0.0)));
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
	return Variable(F64_M3(i_a->GET_DATA(F64_V3), i_b->GET_DATA(F64_V3), i_c->GET_DATA(F64_V3)));
}

NODES::CAST::MAKE::Mat4::Mat4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_a = DATA_I("A", Variable(F64_V4(0.0)));
	i_b = DATA_I("B", Variable(F64_V4(0.0)));
	i_c = DATA_I("C", Variable(F64_V4(0.0)));
	i_d = DATA_I("D", Variable(F64_V4(0.0)));
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
	return Variable(F64_M4(i_a->GET_DATA(F64_V4), i_b->GET_DATA(F64_V4), i_c->GET_DATA(F64_V4), i_d->GET_DATA(F64_V4)));
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
	case 0: return Variable(i_a->GET_DATA(F64) + i_b->GET_DATA(F64));
	case 1: return Variable(i_a->GET_DATA(F64) - i_b->GET_DATA(F64));
	case 2: return Variable(i_a->GET_DATA(F64) * i_b->GET_DATA(F64));
	case 3: return Variable(i_a->GET_DATA(F64) / i_b->GET_DATA(F64));
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
	const F64 x = in->GET_DATA(F64);
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
	if (port == out.get()) {
		return true;
	}

	const VAR_TYPE incoming_type = conn->getDataO()->var_type;
	if (port == in_a.get()) {
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
	if (port == in_b.get()) {
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

NODES::SINGLETON::Camera_2D::Camera_2D() :
	Node("2D Camera")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(100);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	center = DATA_I("Color", Variable(F64_V2(0,0)));
	zoom = DATA_I("Color", Variable(1.0));
}

void NODES::SINGLETON::Camera_2D::exec(const Port* port) {
	SESSION->viewport->center_2d = center->GET_DATA(F64_V2);
	SESSION->viewport->zoom_2d = zoom->GET_DATA(F64);
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