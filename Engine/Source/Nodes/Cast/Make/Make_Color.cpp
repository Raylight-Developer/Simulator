#include "Nodes/Cast/Make/Make_Color.hpp"

NODES::CAST::MAKE::Color::Color() :
	Node(Node_Type::CAST_MAKE_COLOR, "Make")
{
	rect.setWidth(60);
	rect.setHeight(120);

	di_r = DATA_I("R", Variable(0.0));
	di_g = DATA_I("G", Variable(0.0));
	di_b = DATA_I("B", Variable(0.0));
	di_a = DATA_I("A", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::COLOR);
}

Ptr_S<Variable> NODES::CAST::MAKE::Color::getData(const Port* port) {
	return make_shared<Variable>(::Color(*di_r->GET_DATA(F64), *di_g->GET_DATA(F64), *di_b->GET_DATA(F64), *di_a->GET_DATA(F64)));
}