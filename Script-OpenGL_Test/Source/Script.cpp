#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("OpenGL Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	PRINT(NL << "Loaded OpenGL Script");

	header_color = QColor(75, 25, 25);
	rect.setWidth(140);
	rect.setHeight(60);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");
}

void Script::onUnload() {
	PRINT(NL << "Unloaded OpenGL Script");
	Session::destroy();
}

void Script::exec(const Exec_I* port) {
	render();
	exec_out->exec();
}

void Script::render() {
	const Color u_color  = Color(1, 0.4, 0, 1);

	RENDER::Dim_2D::Line(F32_V2(60, 60), F32_V2(-60, 60), 4, u_color);

	RENDER::Dim_2D::RoundedLine(F32_V2(  60, 60), F32_V2( 100, 20), 4, u_color);
	RENDER::Dim_2D::RoundedLine(F32_V2( -60, 60), F32_V2(-100, 20), 4, u_color);

	RENDER::Dim_2D::Line(F32_V2( 100, 20), F32_V2( 160, 10), 4, u_color);
	RENDER::Dim_2D::Line(F32_V2(-100, 20), F32_V2(-160, 10), 4, u_color);

	RENDER::Dim_2D::RoundedLine(F32_V2( 160, 10), F32_V2( 170, -40), 4, u_color);
	RENDER::Dim_2D::RoundedLine(F32_V2(-160, 10), F32_V2(-170, -40), 4, u_color);

	RENDER::Dim_2D::Line(F32_V2( 170, -40), F32_V2( 130, -40), 4, u_color);
	RENDER::Dim_2D::Line(F32_V2(-170, -40), F32_V2(-130, -40), 4, u_color);

	RENDER::Dim_2D::Line(F32_V2(30, -40), F32_V2(-30, -40), 4, u_color);

	RENDER::Dim_2D::Circle(F32_V2( 80, -40), 40, u_color);
	RENDER::Dim_2D::Circle(F32_V2(-80, -40), 40, u_color);
}