#include "Nodes/Exec/Loop/For.hpp"

NODES::EXEC::LOOP::For::For() :
	Node(Node_Type::EXEC_LOOP_FOR, "For Loop")
{
	rect.setWidth(160);
	rect.setHeight(100);

	ei_exec  = EXEC_I("");
	di_count = DATA_I("Count", Variable(0LL));

	eo_finished = EXEC_O("Finished");
	eo_for      = EXEC_O("Repeater");
	do_i        = DATA_O("i", VAR_TYPE::INT);

	for_i = 0;
}

void NODES::EXEC::LOOP::For::exec(const Port* port) {
	node_error = false;
	if (!di_count->connected()) {
		node_error = true;
		return;
	}
	const I64 for_count = *di_count->GET_DATA(I64);
	for (I64 i = 0; i < for_count; i++) {
		for_i = i;
		eo_for->exec();
	}
	eo_finished->exec();
}

Ptr_S<Variable> NODES::EXEC::LOOP::For::getData(const Port* port) {
	return make_shared<Variable>(for_i);
}