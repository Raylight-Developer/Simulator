#include "Nodes/Cast/Make/Make_Mat4.hpp"

NODES::CAST::MAKE::Mat4::Mat4() :
	Node(Node_Type::CAST_MAKE_MAT4, "Make")
{
	rect.setWidth(60);
	rect.setHeight(120);

	di_col_x = DATA_I("X", Variable(0.0));
	di_col_y = DATA_I("Y", Variable(0.0));
	di_col_z = DATA_I("Z", Variable(0.0));
	di_col_w = DATA_I("W", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::MAT4);
}

Ptr_S<Variable> NODES::CAST::MAKE::Mat4::getData(const Port* port) {
	return make_shared<Variable>(F64_M4(*di_col_x->GET_DATA(F64_V4), *di_col_y->GET_DATA(F64_V4), *di_col_z->GET_DATA(F64_V4), *di_col_w->GET_DATA(F64_V4)));
}