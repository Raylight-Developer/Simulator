#include "Nodes/Exec/Loop/While.hpp"

NODES::EXEC::LOOP::While::While() :
	Node(Node_Type::EXEC_LOOP_WHILE, "While Loop")
{
	rect.setWidth(160);
	rect.setHeight(80);

	ei_exec = EXEC_I("");
	di_cond = DATA_I("Cond", Variable(false));

	eo_finished = EXEC_O("Finished");
	eo_while      = EXEC_O("Repeater");
}

void NODES::EXEC::LOOP::While::exec(const Port* port) {
	node_error = false;
	if (!di_cond->connected()) {
		node_error = true;
		return;
	}
	const bool while_condition = *di_cond->GET_DATA(bool);
	while (while_condition) {
		eo_while->exec();
	}
	eo_finished->exec();
}