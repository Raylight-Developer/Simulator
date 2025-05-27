#include "Nodes/Hook/Display.hpp"

#include "Session.hpp"

NODES::HOOK::Display::Display() :
	Node(Node_Type::HOOK_DISPLAY, "Display")
{
	rect.setWidth(120);
	rect.setHeight(100);

	do_resolution = DATA_O("Pixels", VAR_TYPE::VEC2);

	do_camera_pos = DATA_O("Camera Pos", VAR_TYPE::VEC2);
	do_camera_zoom = DATA_O("Camera Zoom", VAR_TYPE::DOUBLE);
}

Ptr_S<Variable> NODES::HOOK::Display::getData(const Port* port) {
	if (port == do_resolution.get()) {
		return make_shared<Variable>(SIM_HOOK.viewport_resolution);
	}
	else if (port == do_camera_pos.get()) {
		return make_shared<Variable>(SIM_HOOK.camera_pos_2d);
	}
	return make_shared<Variable>(SIM_HOOK.camera_zoom_2d);
}