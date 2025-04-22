	#include "Nodes/Singleton/Euler_Tick.hpp"

#include "Session.hpp"

NODES::SINGLETON::Euler_Tick::Euler_Tick() :
	Node(Node_Type::SINGLETON_EULER_TICK, "Tick")
{
	rect.setWidth(100);
	rect.setHeight(140);

	exec_out  = EXEC_O("Tick");
	o_delta   = DATA_O("Delta", VAR_TYPE::DOUBLE);
	o_calls   = DATA_O("Calls", VAR_TYPE::INT);
	o_runtime = DATA_O("Runtime", VAR_TYPE::DOUBLE);

	delta = 0;
}

void NODES::SINGLETON::Euler_Tick::exec(const F64& _delta) {
	delta = _delta;
	exec_out->exec();
}

Variable NODES::SINGLETON::Euler_Tick::getData(const Port* port) const {
	if (port == o_delta.get())
		return Variable(delta);
	if (port == o_calls.get())
		return Variable(SESSION->current_frame);
	if (port == o_runtime.get())
		return Variable(chrono::duration<F64>(NOW - SESSION->start).count());
	return Variable();
}

// TODO override type()  , optimize lookup in other places