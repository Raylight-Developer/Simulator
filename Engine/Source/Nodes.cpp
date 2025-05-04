#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

// TODO optimize lookup of QGraphicsItem if neccesary using node_type

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

Ptr_S<Variable> NODES::CAST::MAKE::Vec2::getData(const Port* port) {
	return make_shared<Variable>(F64_V2(*i_x->GET_DATA(F64), *i_y->GET_DATA(F64)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Vec3::getData(const Port* port) {
	return make_shared<Variable>(F64_V3(*i_x->GET_DATA(F64), *i_y->GET_DATA(F64), *i_z->GET_DATA(F64)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Vec4::getData(const Port* port) {
	return make_shared<Variable>(F64_V4(*i_x->GET_DATA(F64), *i_y->GET_DATA(F64), *i_z->GET_DATA(F64), *i_w->GET_DATA(F64)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Quat::getData(const Port* port) {
	return make_shared<Variable>(F64_Quat(*i_w->GET_DATA(F64), *i_x->GET_DATA(F64), *i_y->GET_DATA(F64), *i_z->GET_DATA(F64)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Mat2::getData(const Port* port) {
	return make_shared<Variable>(F64_M2(*i_a->GET_DATA(F64_V2), *i_b->GET_DATA(F64_V2)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Mat3::getData(const Port* port) {
	return make_shared<Variable>(F64_M3(*i_a->GET_DATA(F64_V3), *i_b->GET_DATA(F64_V3), *i_c->GET_DATA(F64_V3)));
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

Ptr_S<Variable> NODES::CAST::MAKE::Mat4::getData(const Port* port) {
	return make_shared<Variable>(F64_M4(*i_a->GET_DATA(F64_V4), *i_b->GET_DATA(F64_V4), *i_c->GET_DATA(F64_V4), *i_d->GET_DATA(F64_V4)));
}

void Node::save(CORE::Lace& lace, const U64& index) const {
	lace NL << "┌Node [ " << index << " ] " << label;
	lace++;
	lace NL PTR(shared_from_this().get());
	lace NL << "Type " << NODES::toString(node_type);
	lace NL << "( " << pos() << " )";
	lace NL << "┌In( " << inputs.size() << " )";
	lace++;
	for (Port* port : inputs) {
		lace NL PTR(port);
	}
	lace--;
	lace NL << "└In";
	lace NL << "┌Out( " << outputs.size() << " )";
	lace++;
	for (Port* port : outputs) {
		lace NL PTR(port);
	}
	lace--;
	lace NL << "└Out";

	lace NL << "┌Data";
	lace++;
	saveDetail(lace);
	lace--;
	lace NL << "└Data";

	lace--;
	lace NL << "└Node";
}

void Node::load(File* file, const Token_Array& tokens) {
	const string  r_label = f_join(tokens[0], 4);
	const U64     r_ptr   = stoU64(tokens[1][1]);
	const string  r_type  = tokens[2][1];
	const QPointF r_pos   = QPointF(stoF64(tokens[3][1]), stoF64(tokens[3][2]));

	const NODES::Node_Type r_node_type  = NODES::toEnum(r_type);

	Ptr_S<Node> node = NODES::node_get_map.at(r_node_type)();

	if (node == nullptr and r_node_type == NODES::Node_Type::SCRIPT) {
		Token_Array detail_data = File::getBlock("┌Data", "└Data", tokens);
		const string script_path = f_join(detail_data[0]);

		node = Ptr_S<NODES::SCRIPT::Script>(NODES::SCRIPT::loadScript(qstr(script_path)));
	}

	if (node) {
		node->label = qstr(r_label);

		SESSION->window->node_editor->scene->addItem(node.get());
		node->setPos(r_pos);

		file->pointer_map.set(r_ptr, to_U(node.get()));
		file->nodes.push(node);

		Token_Array inputs  = File::getBlock("┌In(" , "└In" , tokens);
		Token_Array outputs = File::getBlock("┌Out(", "└Out", tokens);

		for (U64 i = 0; i < inputs.size(); i++) {
			file->pointer_map.set(stoU64(inputs[i][1]), to_U(node->inputs[i]));
		}
		for (U64 i = 0; i < outputs.size(); i++) {
			file->pointer_map.set(stoU64(outputs[i][1]), to_U(node->outputs[i]));
		}

		Token_Array detail_data = File::getBlock("┌Data", "└Data", tokens);
		node->loadDetail(detail_data);
	}
}

string NODES::toString(const Node_Type& value) {
	for (auto& [e, name] : enum_str_map) {
		if (e == value) {
			return string(name);
		}
	}
	return "NONE";
}

NODES::Node_Type NODES::toEnum(const string_view& name) {
	for (auto& [e, str] : enum_str_map) {
		if (str == name) {
			return e;
		}
	}
	return Node_Type::NONE;
}