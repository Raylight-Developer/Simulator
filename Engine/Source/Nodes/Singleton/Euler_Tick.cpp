	#include "Nodes/Singleton/Euler_Tick.hpp"

#include "Session.hpp"

NODES::SINGLETON::Euler_Tick::Euler_Tick() :
	Node(Node_Type::SINGLETON_EULER_TICK, "Tick")
{
	rect.setWidth(100);
	rect.setHeight(120);

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

const Ptr_S<Variable> NODES::SINGLETON::Euler_Tick::getData(const Port* port) const {
	if (port == o_delta.get())
		return make_shared<Variable>(delta);
	if (port == o_calls.get())
		return make_shared<Variable>(static_cast<I64>(SESSION->hook.current_frame));
	if (port == o_runtime.get())
		return make_shared<Variable>(chrono::duration<F64>(NOW - SESSION->hook.playback_start).count());
	return nullptr;
}

void NODES::SINGLETON::Euler_Tick::loadDetail() {
	FILE.euler_tick = static_pointer_cast<Euler_Tick>(shared_from_this());
	FILE.node_singletons.push(shared_from_this());
}