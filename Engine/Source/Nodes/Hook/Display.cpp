#include "Nodes/Hook/Display.hpp"

#include "Session.hpp"

NODES::HOOK::Display::Display() :
	Node("Display")
{
	rect.setWidth(120);
	rect.setHeight(100);
}

Variable NODES::HOOK::Display::getData(const Port* port) const {
	return Variable();
}