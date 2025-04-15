#include "Nodes/Exec/Subsample.hpp"

#include "Session.hpp"

NODES::EXEC::Subsample::Subsample() :
	Node("Subsample")
{
}

void NODES::EXEC::Subsample::exec(const Port* port) {
	exec_out->exec();
}

Variable NODES::EXEC::Subsample::getData(const Port* port) const {
	if (port == o_delta)
		return Variable(delta);
	if (port == o_calls)
		return Variable(SESSION->current_frame);
	if (port == o_runtime)
		return Variable(chrono::duration<double>(NOW - SESSION->start).count());
	return Variable();
}