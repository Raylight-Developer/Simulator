#include "Nodes/Hook/Input/Mouse_Pos.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse_Pos::Mouse_Pos() :
	Node("Mouse Pos")
{
	rect.setWidth(120);
	rect.setHeight(100);
}

Variable NODES::HOOK::INPUT::Mouse_Pos::getData(const Port* port) const {
	return Variable();
}