#include "Nodes/Hook/Input/Key.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Key::Key() :
	Node("HOOK::INPUT::KEY", "Key")
{
	rect.setWidth(120);
	rect.setHeight(100);
}

Variable NODES::HOOK::INPUT::Key::getData(const Port* port) const {
	return Variable();
}