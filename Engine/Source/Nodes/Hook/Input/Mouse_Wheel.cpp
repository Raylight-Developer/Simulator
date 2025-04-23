#include "Nodes/Hook/Input/Mouse_Wheel.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Wheel::Mouse_Wheel() :
	Node(Node_Type::NONE, "Mouse Wheel")
{
	rect.setWidth(120);
	rect.setHeight(80);

	angle_x = DATA_O("Angle X", VAR_TYPE::INT);
	angle_y = DATA_O("Angle Y", VAR_TYPE::INT);
}

Variable NODES::HOOK::INPUT::Mouse_Wheel::getData(const Port* port) const {
	if (port == angle_x.get()) {
		return Variable(static_cast<I64>(SESSION->hook.mouse_wheel.x));
	}
	return Variable(static_cast<I64>(SESSION->hook.mouse_wheel.y));
}