#include "Nodes/Rendering/2D/Line.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

NODES::RENDERING::DIM_2D::Line::Line() :
	Node(Node_Type::RENDER_2D_LINE, "Line")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(F64_V2(-200, -200)));
	vert_b = DATA_I("B", Variable(F64_V2( 200,  200)));
	width  = DATA_I("Width", Variable(3.0));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Line::render() {
	// Update vertices
	const auto v1      = to_F32(*vert_a->GET_DATA(F64_V2));
	const auto v2      = to_F32(*vert_b->GET_DATA(F64_V2));
	const auto radius  = to_F32(*width ->GET_DATA(F64));
	const auto u_color = *color->GET_DATA(Color);

	RENDER::Dim_2D::Line(v1, v2, radius, u_color);
}

void NODES::RENDERING::DIM_2D::Line::exec(const Port* port) {
	render();
	exec_out->exec();
}