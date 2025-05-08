#include "Nodes/Cast/Convert/I64_To_F64.hpp"

NODES::CAST::CONVERT::I64_To_F64::I64_To_F64() :
	Node(Node_Type::CAST_CONVERT_I64_TO_F64, "->")
{
	rect.setWidth(60);
	rect.setHeight(60);

	di_val = DATA_I("", Variable(0LL));
	do_res = DATA_O("", VAR_TYPE::DOUBLE);
}

Ptr_S<Variable> NODES::CAST::CONVERT::I64_To_F64::getData(const Port* port) {
	return make_shared<Variable>(to_F64(*di_val->GET_DATA(I64)));
}