#include "Nodes/Boolean/Select.hpp"

NODES::BOOLEAN::Select::Select() :
	Node(Node_Type::BOOLEAN_SELECT, "Select")
{
	rect.setWidth(80);
	rect.setHeight(100);

	condition  = DATA_I("", Variable(false));
	i_true     = DATA_I("True", VAR_TYPE::NONE);
	i_false    = DATA_I("False", VAR_TYPE::NONE);
	out        = DATA_O("", VAR_TYPE::NONE);
}

Ptr_S<Variable> NODES::BOOLEAN::Select::getData(const Port* port) {
	if (*condition->GET_DATA(bool)) {
		return i_true->getData();
	}
	return i_false->getData();
}