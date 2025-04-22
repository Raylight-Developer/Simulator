#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

NODES::CAST::MAKE::Vec2::Vec2() :
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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
	Node(Node_Type::NONE, "Make")
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

NODES::SINGLETON::Camera_2D::Camera_2D() :
	Node(Node_Type::NONE, "2D Camera")
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
	Node(Node_Type::NONE, "3D Camera")
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

string NODES::toString(const Node_Type& value) {
	for (auto& [e, name] : enumMap) {
		if (e == value) {
			return string(name);
		}
	}
	return "NONE";
}

NODES::Node_Type NODES::toEnum(const string_view& name) {
	for (auto& [e, str] : enumMap) {
		if (str == name) {
			return e;
		}
	}
	return Node_Type::NONE;
}