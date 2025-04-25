#include "Nodes/Exec/Subsample.hpp"

#include "Session.hpp"

NODES::EXEC::Subsample::Subsample() :
	Node(Node_Type::NONE, "Subsample")
{
	rect.setWidth(160);
	rect.setHeight(140);

	exec_in   = EXEC_I("");
	delta_in  = DATA_I("Delta", Variable(0.004166666));
	count_in  = DATA_I("Samples", Variable(4LL));

	exec_out    = EXEC_O("Finished");
	samples_out = EXEC_O("Tick");
	o_delta     = DATA_O("Delta", VAR_TYPE::DOUBLE);
	o_calls     = DATA_O("Calls", VAR_TYPE::INT);
	o_runtime   = DATA_O("Runtime", VAR_TYPE::DOUBLE);

	calls = 0;
}

void NODES::EXEC::Subsample::exec(const Port* port) {
	const I64 count = *count_in->GET_DATA(I64);
	for (I64 i = 0; i < count; i++) {
		calls++;
		exec_out->exec();
	}
	samples_out->exec();
}

const Ptr_S<Variable> NODES::EXEC::Subsample::getData(const Port* port) const {
	if (port == o_delta.get()) {
		return make_shared<Variable>(*delta_in->GET_DATA(F64) / *count_in->GET_DATA(I64));
	}
	if (port == o_calls.get()) {
		return make_shared<Variable>(calls);
	}
	return make_shared<Variable>(chrono::duration<F64>(NOW - SESSION->hook.playback_start).count());
}