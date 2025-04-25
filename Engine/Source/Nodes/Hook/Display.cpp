#include "Nodes/Hook/Display.hpp"

#include "Session.hpp"

NODES::HOOK::Display::Display() :
	Node(Node_Type::NONE, "Resolution")
{
	rect.setWidth(120);
	rect.setHeight(60);

	resolution = DATA_O("Pixels", VAR_TYPE::VEC2);
}

Ptr_S<Variable> NODES::HOOK::Display::getData(const Port* port) {
	return make_shared<Variable>(SESSION->hook.viewport_resolution);
}