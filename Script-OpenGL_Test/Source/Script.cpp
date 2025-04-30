#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("OpenGL Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	PRINT(NL << "Loaded OpenGL Script");

	header_color = QColor(75, 25, 25);
	rect.setWidth(140);
	rect.setHeight(80);

	exec_in  = EXEC_I("");
	move_speed = DATA_I("Speed", Variable(1.0));

	exec_out = EXEC_O("");

	out_color = Color(1, 1, 1, 1);
	car_pos = F64_V2(0, 0);
}

void Script::onUnload() {
	PRINT(NL << "Unloaded OpenGL Script");
	Session::destroy();
}

void Script::exec(const Exec_I* port) {
	if (SESSION->hook.input_down["1"]) {
		out_color = Color(1, 1, 1, 1);
	}
	else if (SESSION->hook.input_down["2"]) {
		out_color = Color(1, 0, 0, 1);
	}
	else if (SESSION->hook.input_down["3"]) {
		out_color = Color(0, 1, 0, 1);
	}
	else if (SESSION->hook.input_down["4"]) {
		out_color = Color(0, 0, 1, 1);
	}

	const F64 speed = SESSION->viewport->delta_time * (*move_speed->GET_DATA(F64));

	if (SESSION->hook.input_down["A"]) {
		car_pos.x -= speed;
	}
	if (SESSION->hook.input_down["D"]) {
		car_pos.x += speed;
	}
	if (SESSION->hook.input_down["W"]) {
		car_pos.y += speed;
	}
	if (SESSION->hook.input_down["S"]) {
		car_pos.y -= speed;
	}

	render();
	exec_out->exec();
}

void Script::render() {
	Color u_color = out_color;

	if (SESSION->hook.input_down["5"]) {
		u_color = Color(1, 1, 0, 1);
	}
	else if (SESSION->hook.input_down["6"]) {
		u_color = Color(0, 1, 1, 1);
	}
	else if (SESSION->hook.input_down["7"]) {
		u_color = Color(1, 0, 1, 1);
	}

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(60, 60), car_pos + F32_V2(-60, 60), 4, u_color);

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(  60, 60), car_pos + F32_V2( 100, 20), 4, u_color);
	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2( -60, 60), car_pos + F32_V2(-100, 20), 4, u_color);

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2( 100, 20), car_pos + F32_V2( 160, 10), 4, u_color);
	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(-100, 20), car_pos + F32_V2(-160, 10), 4, u_color);

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2( 160, 10), car_pos + F32_V2( 170, -40), 4, u_color);
	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(-160, 10), car_pos + F32_V2(-170, -40), 4, u_color);

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2( 170, -40), car_pos + F32_V2( 130, -40), 4, u_color);
	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(-170, -40), car_pos + F32_V2(-130, -40), 4, u_color);

	RENDER::Dim_2D::RoundedLine(car_pos + F32_V2(30, -40), car_pos + F32_V2(-30, -40), 4, u_color);

	RENDER::Dim_2D::Circle(car_pos + F32_V2( 80, -40), 40, u_color);
	RENDER::Dim_2D::Circle(car_pos + F32_V2(-80, -40), 40, u_color);
}