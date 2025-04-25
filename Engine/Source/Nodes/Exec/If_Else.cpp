#include "Nodes/Exec/If_Else.hpp"

NODES::EXEC::If_Else::If_Else() :
	Node(Node_Type::NONE, "If Else")
{
	rect.setWidth(100);
	rect.setHeight(80);

	in = EXEC_I("");
	condition = DATA_I("", Variable(false));
	out_a = EXEC_O("True");
	out_b = EXEC_O("False");
}

void NODES::EXEC::If_Else::exec(const Port* port) {
	if (*condition->GET_DATA(bool)) {
		out_a->exec();
	}
	else {
		out_b->exec();
	}
}