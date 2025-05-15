#include "Nodes/Cast/Break/Break_Vec2.hpp"

NODES::CAST::BREAK::Vec2::Vec2() :
	Node(Node_Type::CAST_BREAK_VEC2, "Break")
{
	rect.setWidth(60);
	rect.setHeight(80);

	di_val = DATA_I("", Variable(F64_V2(0.0, 0.0)));

	do_x = DATA_O("X", VAR_TYPE::DOUBLE);
	do_y = DATA_O("Y", VAR_TYPE::DOUBLE);
}

Ptr_S<Variable> NODES::CAST::BREAK::Vec2::getData(const Port* port) {
	if (port == do_x.get()) {
		return make_shared<Variable>(di_val->GET_DATA(F64_V2)->x);
	}
	return make_shared<Variable>(di_val->GET_DATA(F64_V2)->y);
}