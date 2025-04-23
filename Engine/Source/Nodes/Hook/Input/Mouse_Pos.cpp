#include "Nodes/Hook/Input/Mouse_Pos.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Pos::Mouse_Pos() :
	Node(Node_Type::NONE, "Mouse Pos")
{
	rect.setWidth(120);
	rect.setHeight(100);

	screen_pos   = DATA_O("Pos", VAR_TYPE::VEC2);
	is_on_screen = DATA_O("On Screen", VAR_TYPE::BOOL);
}

Variable NODES::HOOK::INPUT::Mouse_Pos::getData(const Port* port) const {
	if (port == screen_pos.get()) {
		return Variable(SESSION->hook.mouse_pos);
	}
	return Variable(SESSION->hook.mouse_on_screen);
}