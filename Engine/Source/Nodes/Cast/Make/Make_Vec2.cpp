#include "Nodes/Cast/Make/Make_Vec2.hpp"

NODES::CAST::MAKE::Vec2::Vec2() :
	Node(Node_Type::CAST_MAKE_VEC2, "Make")
{
	rect.setWidth(60);
	rect.setHeight(80);

	di_x = DATA_I("X", Variable(0.0));
	di_y = DATA_I("Y", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::VEC2);
}

Ptr_S<Variable> NODES::CAST::MAKE::Vec2::getData(const Port* port) {
	return make_shared<Variable>(F64_V2(*di_x->GET_DATA(F64), *di_y->GET_DATA(F64)));
}