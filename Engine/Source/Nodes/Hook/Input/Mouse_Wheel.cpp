#include "Nodes/Hook/Input/Mouse_Wheel.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Wheel::Mouse_Wheel() :
	Node("HOOK::INPUT::MOUSE_WHEEL", "Mouse Wheel")
{
	rect.setWidth(120);
	rect.setHeight(100);
}

Variable NODES::HOOK::INPUT::Mouse_Wheel::getData(const Port* port) const {
	return Variable();
}