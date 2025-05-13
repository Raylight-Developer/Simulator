#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Controllable", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {

	rect.setWidth(140);
	rect.setHeight(80);

	ei_exec       = EXEC_I("");
	di_move_speed = DATA_I("Speed", Variable(1.0));

	eo_exec = EXEC_O("");

	out_color = Color(1, 1, 1, 1);
	car_pos = F64_V2(0, 0);


	SESSION->hook.onKeyDown[this] = [this](const string& key) {
		if (key == "1") {
			out_color = Color(1, 1, 1, 1);
		}
		else if (key == "2") {
			out_color = Color(1, 0, 0, 1);
		}
		else if (key == "3") {
			out_color = Color(0, 1, 0, 1);
		}
		else if (key == "4") {
			out_color = Color(0, 0, 1, 1);
		}
	};

	LOGL(<< "Loaded Controllable Object Script");
}

void Script::onUnload() {
	SESSION->hook.onKeyDown.remove(this);

	LOGL(<< "Unloaded Controllable Object Script");
}

void Script::exec(const Exec_I* port) {
	const F64 speed = SESSION->hook.delta_time * (*di_move_speed->GET_DATA(F64));
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
	eo_exec->exec();
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