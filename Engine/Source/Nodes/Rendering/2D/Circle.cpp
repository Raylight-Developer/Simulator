#include "Nodes/Rendering/2D/Circle.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

NODES::RENDERING::DIM_2D::Circle::Circle() :
	Node(Node_Type::NONE, "Circle")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(120);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	center = DATA_I("Center", Variable(F64_V2(0, 0)));
	radius = DATA_I("Radius", Variable(50.0));
	color  = DATA_I("Color" , Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Circle::render() {
	const auto u_center = to_F32(center->GET_DATA(F64_V2));
	const auto u_radius = to_F32(radius->GET_DATA(F64));
	const auto u_color  = color->GET_DATA(Color);

	RENDER::Dim_2D::Circle(u_center, u_radius, u_color);
}

void NODES::RENDERING::DIM_2D::Circle::exec(const Port* port) {
	render();
	exec_out->exec();
}