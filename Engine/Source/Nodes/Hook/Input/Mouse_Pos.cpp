#include "Nodes/Hook/Input/Mouse_Pos.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Pos::Mouse_Pos() :
	Node(Node_Type::HOOK_INPUT_MOUSE_POS, "Mouse Pos")
{
	rect.setWidth(100);
	rect.setHeight(80);

	screen_pos   = DATA_O("Pos", VAR_TYPE::VEC2);
	is_on_screen = DATA_O("Valid", VAR_TYPE::BOOL);
}

Ptr_S<Variable> NODES::HOOK::INPUT::Mouse_Pos::getData(const Port* port) {
	if (port == screen_pos.get()) {
		return make_shared<Variable>(SESSION->hook.mouse_pos);
	}
	return make_shared<Variable>(SESSION->hook.mouse_on_screen);
}