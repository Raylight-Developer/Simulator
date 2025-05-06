	#include "Nodes/Singleton/Euler_Tick.hpp"

#include "Session.hpp"

NODES::SINGLETON::Euler_Tick::Euler_Tick() :
	Node(Node_Type::SINGLETON_EULER_TICK, "Tick")
{
	rect.setWidth(100);
	rect.setHeight(120);

	eo_exec    = EXEC_O("Tick");
	do_delta   = DATA_O("Delta", VAR_TYPE::DOUBLE);
	do_calls   = DATA_O("Calls", VAR_TYPE::INT);
	do_runtime = DATA_O("Runtime", VAR_TYPE::DOUBLE);

	delta = 0;
	runtime = 0.0;
}

void NODES::SINGLETON::Euler_Tick::exec(const F64& _delta) {
	delta = _delta;
	runtime += delta;
	eo_exec->exec();
}

Ptr_S<Variable> NODES::SINGLETON::Euler_Tick::getData(const Port* port) {
	if (port == do_delta.get())
		return make_shared<Variable>(delta);
	if (port == do_calls.get())
		return make_shared<Variable>(static_cast<I64>(SESSION->hook.current_frame));
	if (port == do_runtime.get())
		return make_shared<Variable>(runtime);
	return nullptr;
}

void NODES::SINGLETON::Euler_Tick::loadDetail(const Token_Array& tokens) {
	FILE.euler_tick = static_pointer_cast<Euler_Tick>(shared_from_this());
	FILE.node_singletons.push(shared_from_this());
}