#include "Nodes/Cast/Make/Make_Mat3.hpp"

NODES::CAST::MAKE::Mat3::Mat3() :
	Node(Node_Type::CAST_MAKE_MAT3, "Make")
{
	rect.setWidth(60);
	rect.setHeight(100);

	di_col_x = DATA_I("X", Variable(0.0));
	di_col_y = DATA_I("Y", Variable(0.0));
	di_col_z = DATA_I("Z", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::MAT3);
}

Ptr_S<Variable> NODES::CAST::MAKE::Mat3::getData(const Port* port) {
	return make_shared<Variable>(F64_M3(*di_col_x->GET_DATA(F64_V3), *di_col_y->GET_DATA(F64_V3), *di_col_z->GET_DATA(F64_V3)));
}