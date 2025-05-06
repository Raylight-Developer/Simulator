#include "Nodes/Exec/Loop/Subsample.hpp"

#include "Session.hpp"

NODES::EXEC::LOOP::Subsample::Subsample() :
	Node(Node_Type::EXEC_LOOP_SUBSAMPLE, "Subsample")
{
	rect.setWidth(160);
	rect.setHeight(140);

	ei_exec   = EXEC_I("");
	di_delta  = DATA_I("Delta", Variable(0.004166666));
	di_count  = DATA_I("Samples", Variable(4LL));

	eo_finished    = EXEC_O("Finished");
	eo_sample = EXEC_O("Tick");
	do_delta     = DATA_O("Delta", VAR_TYPE::DOUBLE);
	do_calls     = DATA_O("Calls", VAR_TYPE::INT);
	do_runtime   = DATA_O("Runtime", VAR_TYPE::DOUBLE);

	calls = 0;
}

void NODES::EXEC::LOOP::Subsample::exec(const Port* port) {
	node_error = false;
	if (!(di_delta->connected() && di_count->connected())) {
		node_error = true;
		return;
	}
	const I64 count = *di_count->GET_DATA(I64);
	for (I64 i = 0; i < count; i++) {
		calls++;
		eo_finished->exec();
	}
	eo_sample->exec();
}

Ptr_S<Variable> NODES::EXEC::LOOP::Subsample::getData(const Port* port) {
	if (port == do_delta.get()) {
		return make_shared<Variable>(*di_delta->GET_DATA(F64) / *di_count->GET_DATA(I64));
	}
	if (port == do_calls.get()) {
		return make_shared<Variable>(calls);
	}
	return make_shared<Variable>(chrono::duration<F64>(NOW - SESSION->hook.playback_start).count());
}