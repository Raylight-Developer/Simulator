#include "Nodes/Exec/If.hpp"

NODES::EXEC::If::If() :
	Node("If")
{
	rect.setWidth(40);
	rect.setHeight(80);

	in = EXEC_I("");
	condition = DATA_I("", Variable(false));
	out = EXEC_O("");
}

void NODES::EXEC::If::exec(const Port* port) {
	if (condition->GET_DATA(bool)) {
		out ->exec();
	}
}