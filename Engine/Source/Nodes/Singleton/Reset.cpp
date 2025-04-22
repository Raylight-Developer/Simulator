#include "Nodes/Singleton/Reset.hpp"

NODES::SINGLETON::Reset::Reset() :
	Node(Node_Type::SINGLETON_RESET, "Reset")
{
	rect.setWidth(80);
	rect.setHeight(80);

	exec_out = EXEC_O("Once");
	bool_out = DATA_O("True", VAR_TYPE::BOOL);
}

void NODES::SINGLETON::Reset::exec() {
	exec_out->exec();
}

Variable NODES::SINGLETON::Reset::getData(const Port* port) const {
	return Variable(true);
}