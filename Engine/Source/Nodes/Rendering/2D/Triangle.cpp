#include "Nodes/Rendering/2D/Triangle.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

NODES::RENDERING::DIM_2D::Triangle::Triangle() :
	Node(Node_Type::NONE, "Tri")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(140);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	vert_a = DATA_I("A", Variable(F64_V2(  0,  57.777)));
	vert_b = DATA_I("B", Variable(F64_V2(-50, -28.868)));
	vert_c = DATA_I("C", Variable(F64_V2( 50, -28.868)));
	color  = DATA_I("Color", Variable(Color(1, 1, 1, 1)));
}

void NODES::RENDERING::DIM_2D::Triangle::render() {
	// Update vertices
	const auto v1      = to_F32(vert_a->GET_DATA(F64_V2));
	const auto v2      = to_F32(vert_b->GET_DATA(F64_V2));
	const auto v3      = to_F32(vert_c->GET_DATA(F64_V2));
	const auto u_color = color ->GET_DATA(Color);

	RENDER::Dim_2D::Triangle(v1, v2, v3, u_color);
}

void NODES::RENDERING::DIM_2D::Triangle::exec(const Port* port) {
	render();
	exec_out->exec();
}