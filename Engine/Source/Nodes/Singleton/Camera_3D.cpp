#include "Nodes/Singleton/Camera_3D.hpp"

#include "Session.hpp"

NODES::SINGLETON::Camera_3D::Camera_3D() :
	Node(Node_Type::NONE, "3D Camera")
{
	header_color = QColor(25, 75, 25);
	rect.setWidth(100);
	rect.setHeight(60);

	ei_exec = EXEC_I("");
	eo_exec = EXEC_O("");
}

void NODES::SINGLETON::Camera_3D::exec(const Port* port) {
	eo_exec->exec();
}