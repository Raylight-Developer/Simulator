#include "Nodes/Singleton/Camera_3D.hpp"

#include "Session.hpp"

NODES::SINGLETON::Camera_3D::Camera_3D() :
	Node(Node_Type::NONE, "3D Camera")
{
	header_color = QColor(25, 75, 25);
	rect.setWidth(100);
	rect.setHeight(60);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");
}

void NODES::SINGLETON::Camera_3D::exec(const Port* port) {
	exec_out->exec();
}