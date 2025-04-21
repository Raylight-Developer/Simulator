#include "Nodes/Hook/Input/Mouse.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse::Mouse() :
	Node("Mouse")
{
	rect.setWidth(120);
	rect.setHeight(100);
}

Variable NODES::HOOK::INPUT::Mouse::getData(const Port* port) const {
	return Variable();
}