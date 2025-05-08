#include "Nodes/Singleton/Init.hpp"

#include "Session.hpp"

NODES::SINGLETON::Init::Init() :
	Node(Node_Type::SINGLETON_INIT, "Init")
{
	rect.setWidth(80);
	rect.setHeight(80);

	eo_exec = EXEC_O("Once");
	do_bool = DATA_O("True", VAR_TYPE::BOOL);
}

void NODES::SINGLETON::Init::exec() {
	eo_exec->exec();
}

Ptr_S<Variable> NODES::SINGLETON::Init::getData(const Port* port) {
	return make_shared<Variable>(true);
}

void NODES::SINGLETON::Init::loadDetail(const Token_Array& tokens) {
	FILE.init = static_pointer_cast<Init>(shared_from_this());
	FILE.node_singletons.push(FILE.init);
}