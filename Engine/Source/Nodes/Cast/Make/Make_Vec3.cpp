#include "Nodes/Cast/Make/Make_Vec3.hpp"

NODES::CAST::MAKE::Vec3::Vec3() :
	Node(Node_Type::CAST_MAKE_VEC3, "Make")
{
	rect.setWidth(60);
	rect.setHeight(100);

	di_x = DATA_I("X", Variable(0.0));
	di_y = DATA_I("Y", Variable(0.0));
	di_z = DATA_I("Z", Variable(0.0));

	do_val = DATA_O("", VAR_TYPE::VEC3);
}

Ptr_S<Variable> NODES::CAST::MAKE::Vec3::getData(const Port* port) {
	return make_shared<Variable>(F64_V3(*di_x->GET_DATA(F64), *di_y->GET_DATA(F64), *di_z->GET_DATA(F64)));
}