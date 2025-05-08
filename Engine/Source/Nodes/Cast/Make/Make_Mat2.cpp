#include "Nodes/Cast/Make/Make_Mat2.hpp"

NODES::CAST::MAKE::Mat2::Mat2() :
	Node(Node_Type::CAST_MAKE_MAT2, "Make")
{
	rect.setWidth(60);
	rect.setHeight(80);

	di_col_x = DATA_I("X", Variable(0.0));
	di_col_y = DATA_I("Y", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::MAT2);
}

Ptr_S<Variable> NODES::CAST::MAKE::Mat2::getData(const Port* port) {
	return make_shared<Variable>(F64_M2(*di_col_x->GET_DATA(F64_V2), *di_col_y->GET_DATA(F64_V2)));
}