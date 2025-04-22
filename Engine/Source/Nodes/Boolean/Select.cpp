#include "Nodes/Boolean/Select.hpp"

NODES::BOOLEAN::Select::Select() :
	Node(Node_Type::NONE, "Select")
{
	rect.setWidth(80);
	rect.setHeight(100);

	condition  = DATA_I("", Variable(false));
	i_true     = DATA_I("True", VAR_TYPE::NONE);
	i_false    = DATA_I("False", VAR_TYPE::NONE);
	out        = DATA_O("", VAR_TYPE::NONE);

	i_true ->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_false->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	out    ->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_true ->onDisconnection = [this](Port* port){ onDisconnection(port); };
	i_false->onDisconnection = [this](Port* port){ onDisconnection(port); };
	out    ->onDisconnection = [this](Port* port){ onDisconnection(port); };
}

bool NODES::BOOLEAN::Select::onConnRequested(Port* port, Connection* conn) {
	return false; // TODO set default var if no connection
}

void NODES::BOOLEAN::Select::onDisconnection(Port * port) {
	// TODO unset defaults
}

Variable NODES::BOOLEAN::Select::getData(const Port* port) const {
	if (condition->GET_DATA(bool)) {
		return i_true->getData();
	}
	return i_false->getData();
}