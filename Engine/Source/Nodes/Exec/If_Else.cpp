#include "Nodes/Exec/If_Else.hpp"

NODES::EXEC::If_Else::If_Else() :
	Node(Node_Type::EXEC_IF_ELSE, "If Else")
{
	rect.setWidth(100);
	rect.setHeight(80);

	ei_exec = EXEC_I("");
	di_cond = DATA_I("", Variable(false));
	eo_true = EXEC_O("True");
	eo_false = EXEC_O("False");
}

void NODES::EXEC::If_Else::exec(const Port* port) {
	if (*di_cond->GET_DATA(bool)) {
		eo_true->exec();
	}
	else {
		eo_false->exec();
	}
}