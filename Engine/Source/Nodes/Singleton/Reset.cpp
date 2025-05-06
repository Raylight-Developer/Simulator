#include "Nodes/Singleton/Reset.hpp"

#include "Session.hpp"

NODES::SINGLETON::Reset::Reset() :
	Node(Node_Type::SINGLETON_RESET, "Reset")
{
	rect.setWidth(80);
	rect.setHeight(80);

	eo_exec = EXEC_O("Once");
	do_bool = DATA_O("True", VAR_TYPE::BOOL);
}

void NODES::SINGLETON::Reset::exec() {
	eo_exec->exec();
}

Ptr_S<Variable> NODES::SINGLETON::Reset::getData(const Port* port) {
	return make_shared<Variable>(true);
}

void NODES::SINGLETON::Reset::loadDetail(const Token_Array& tokens) {
	FILE.reset = static_pointer_cast<Reset>(shared_from_this());
	FILE.node_singletons.push(shared_from_this());
}