#include "Nodes/Rendering/3D/Sphere.hpp"

#include "Session.hpp"
#include "Rendering.hpp"

NODES::RENDERING::DIM_3D::Sphere::Sphere() :
	Node(Node_Type::RENDER_3D_SPHERE, "Sphere")
{
	header_color = QColor(75, 25, 25);
	rect.setWidth(100);
	rect.setHeight(120);

	ei_exec   = EXEC_I("");
	di_center = DATA_I("Center", Variable(F64_V3(0, 0, 0)));
	di_radius = DATA_I("Radius", Variable(1.0));
	di_color  = DATA_I("Color" , Variable(Color(1, 1, 1, 1)));

	eo_exec = EXEC_O("");
}

void NODES::RENDERING::DIM_3D::Sphere::render() {
	auto center = di_center->GET_DATA(F64_V2);
	const auto u_center = to_F32(*di_center->GET_DATA(F64_V3));
	const auto u_radius = to_F32(*di_radius->GET_DATA(F64));
	const auto u_color  = *di_color->GET_DATA(Color);

	RENDER::Dim_3D::Sphere(u_center, u_radius, u_color);
}

void NODES::RENDERING::DIM_3D::Sphere::exec(const Port* port) {
	render();
	eo_exec->exec();
}