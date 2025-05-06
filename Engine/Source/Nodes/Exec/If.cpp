#include "Nodes/Exec/If.hpp"

NODES::EXEC::If::If() :
	Node(Node_Type::EXEC_IF, "If")
{
	rect.setWidth(40);
	rect.setHeight(80);

	ei_exec = EXEC_I("");
	di_cond = DATA_I("", Variable(false));
	eo_exec = EXEC_O("");
}

void NODES::EXEC::If::exec(const Port* port) {
	if (*di_cond->GET_DATA(bool)) {
		eo_exec ->exec();
	}
}