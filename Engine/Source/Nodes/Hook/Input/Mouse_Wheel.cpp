#include "Nodes/Hook/Input/Mouse_Wheel.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Wheel::Mouse_Wheel() :
	Node(Node_Type::HOOK_INPUT_MOUSE_WHEEL, "Mouse Wheel")
{
	rect.setWidth(120);
	rect.setHeight(80);

	do_angle_x = DATA_O("Angle X", VAR_TYPE::INT);
	do_angle_y = DATA_O("Angle Y", VAR_TYPE::INT);
}

Ptr_S<Variable> NODES::HOOK::INPUT::Mouse_Wheel::getData(const Port* port) {
	if (port == do_angle_x.get()) {
		return make_shared<Variable>(static_cast<I64>(SESSION->hook.mouse_wheel.x));
	}
	return make_shared<Variable>(static_cast<I64>(SESSION->hook.mouse_wheel.y));
}