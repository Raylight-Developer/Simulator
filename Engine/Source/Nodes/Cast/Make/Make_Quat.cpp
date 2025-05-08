#include "Nodes/Cast/Make/Make_Quat.hpp"

NODES::CAST::MAKE::Quat::Quat() :
	Node(Node_Type::CAST_MAKE_QUAT, "Make")
{
	rect.setWidth(60);
	rect.setHeight(120);

	di_w = DATA_I("W", Variable(0.0));
	di_x = DATA_I("X", Variable(0.0));
	di_y = DATA_I("Y", Variable(0.0));
	di_z = DATA_I("Z", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::QUAT);
}

Ptr_S<Variable> NODES::CAST::MAKE::Quat::getData(const Port* port) {
	return make_shared<Variable>(F64_Quat(*di_w->GET_DATA(F64), *di_x->GET_DATA(F64), *di_y->GET_DATA(F64), *di_z->GET_DATA(F64)));
}