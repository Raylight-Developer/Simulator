#include "Nodes/Rendering/2D/Triangle.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

NODES::RENDERING::DIM_2D::Triangle::Triangle() :
	Node(Node_Type::RENDER_2D_TRIANGLE, "Tri")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	ei_exec   = EXEC_I("");
	di_vert_a = DATA_I("A", Variable(F64_V2(  0,  57.777)));
	di_vert_b = DATA_I("B", Variable(F64_V2(-50, -28.868)));
	di_vert_c = DATA_I("C", Variable(F64_V2( 50, -28.868)));
	di_color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));

	eo_exec = EXEC_O("");
}

void NODES::RENDERING::DIM_2D::Triangle::render() {
	const auto v1      = to_F32(*di_vert_a->GET_DATA(F64_V2));
	const auto v2      = to_F32(*di_vert_b->GET_DATA(F64_V2));
	const auto v3      = to_F32(*di_vert_c->GET_DATA(F64_V2));
	const auto u_color = *di_color ->GET_DATA(Color);

	RENDER::Dim_2D::Triangle(v1, v2, v3, u_color);
}

void NODES::RENDERING::DIM_2D::Triangle::exec(const Port* port) {
	render();
	eo_exec->exec();
}