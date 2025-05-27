#include "Nodes/Singleton/Camera_2D.hpp"

#include "Session.hpp"

NODES::SINGLETON::Camera_2D::Camera_2D() :
	Node(Node_Type::NONE, "2D Camera")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(100);

	ei_exec  = EXEC_I("");
	di_center = DATA_I("Color", Variable(F64_V2(0,0)));
	di_zoom   = DATA_I("Color", Variable(1.0));

	eo_exec = EXEC_O("");
}

void NODES::SINGLETON::Camera_2D::exec(const Port* port) {
	SIM_HOOK.camera_pos_2d  = *di_center->GET_DATA(F64_V2);
	SIM_HOOK.camera_zoom_2d = *di_zoom->GET_DATA(F64);
	eo_exec->exec();
}