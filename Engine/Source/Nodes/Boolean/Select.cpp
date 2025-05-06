#include "Nodes/Boolean/Select.hpp"

NODES::BOOLEAN::Select::Select() :
	Node(Node_Type::BOOLEAN_SELECT, "Select")
{
	rect.setWidth(80);
	rect.setHeight(100);

	di_cond  = DATA_I("", Variable(false));
	di_true  = DATA_I("True", VAR_TYPE::NONE);
	di_false = DATA_I("False", VAR_TYPE::NONE);

	do_res = DATA_O("", VAR_TYPE::NONE);
}

Ptr_S<Variable> NODES::BOOLEAN::Select::getData(const Port* port) {
	if (*di_cond->GET_DATA(bool)) {
		return di_true->getData();
	}
	return di_false->getData();
}