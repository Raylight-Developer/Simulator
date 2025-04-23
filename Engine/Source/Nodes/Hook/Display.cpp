#include "Nodes/Hook/Display.hpp"

#include "Session.hpp"

NODES::HOOK::Display::Display() :
	Node(Node_Type::NONE, "Resolution")
{
	rect.setWidth(120);
	rect.setHeight(60);

	resolution = DATA_O("Pixels", VAR_TYPE::VEC2);
}

Variable NODES::HOOK::Display::getData(const Port* port) const {
	return Variable(SESSION->hook.viewport_resolution);
}