#include "Nodes/Singleton/Camera_2D.hpp"

#include "Session.hpp"

NODES::SINGLETON::Camera_2D::Camera_2D() :
	Node(Node_Type::NONE, "2D Camera")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(100);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	center = DATA_I("Color", Variable(F64_V2(0,0)));
	zoom   = DATA_I("Color", Variable(1.0));
}

void NODES::SINGLETON::Camera_2D::exec(const Port* port) {
	SESSION->viewport->center_2d = *center->GET_DATA(F64_V2);
	SESSION->viewport->zoom_2d = *zoom->GET_DATA(F64);
	exec_out->exec();
}