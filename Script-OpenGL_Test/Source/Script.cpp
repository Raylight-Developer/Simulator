#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("OpenGL Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	PRINT(NL << "Loaded OpenGL Script");

	header_color = QColor(75, 25, 25);
	rect.setWidth(140);
	rect.setHeight(60);

	exec_in  = new Exec_I(this, "");
	exec_out = new Exec_O(this, "");
}

void Script::onUnload() {
	PRINT(NL << "Unloaded OpenGL Script");
	Session::destroy();
}

void Script::exec(const Port* port) {
	render();
	exec_out->exec();
}

void Script::render() {
	const vec4 u_color  = vec4(1,1,1,1);

	RENDER::Dim_2D::Line(vec2(  60, 60), vec2( -60, 60), 4, u_color);

	RENDER::Dim_2D::Line(vec2(  60, 60), vec2( 100, 20), 4, u_color);
	RENDER::Dim_2D::Line(vec2( -60, 60), vec2(-100, 20), 4, u_color);

	RENDER::Dim_2D::Line(vec2( 100, 20), vec2( 160, 10), 4, u_color);
	RENDER::Dim_2D::Line(vec2(-100, 20), vec2(-160, 10), 4, u_color);

	RENDER::Dim_2D::Line(vec2(30, -40), vec2(-30, -40), 4, u_color);

	RENDER::Dim_2D::Circle(vec2( 80, -40), 40, u_color);
	RENDER::Dim_2D::Circle(vec2(-80, -40), 40, u_color);
}