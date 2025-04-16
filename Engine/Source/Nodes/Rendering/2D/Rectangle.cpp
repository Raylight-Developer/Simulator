#include "Nodes/Rendering/2D/rectangle.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

NODES::RENDERING::DIM_2D::Rectangle::Rectangle() :
	Node("Rect")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(160);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(F64_V2(-100, -100)));
	vert_b = DATA_I("B", Variable(F64_V2(-100,  100)));
	vert_c = DATA_I("C", Variable(F64_V2( 100,  100)));
	vert_d = DATA_I("D", Variable(F64_V2( 100, -100)));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Rectangle::render() {
	const auto v1 = to_F32(vert_a->GET_DATA(F64_V2));
	const auto v2 = to_F32(vert_b->GET_DATA(F64_V2));
	const auto v3 = to_F32(vert_c->GET_DATA(F64_V2));
	const auto v4 = to_F32(vert_d->GET_DATA(F64_V2));
	const auto u_color = color->GET_DATA(Color);

	RENDER::Dim_2D::Rectangle(v1, v2, v3, v4, u_color);
}

void NODES::RENDERING::DIM_2D::Rectangle::exec(const Port* port) {
	render();
	exec_out->exec();
}