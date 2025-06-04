#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Controllable", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(140);
	rect.setHeight(140);

	ei_exec       = EXEC_I("");
	di_move_speed = DATA_I("Speed", Variable(1.0));

	eo_exec = EXEC_O("");
	do_obj_pos = DATA_O("Pos", VAR_TYPE::VEC2);
	do_obj_vel = DATA_O("Vel", VAR_TYPE::VEC2);
	do_obj_rad = DATA_O("Rad", VAR_TYPE::DOUBLE);

	out_color = Color(1, 1, 1, 1);
	obj_pos = F64_V2(0, -10);
	obj_vel = F64_V2(0, 0);
	obj_rad = 10.0;

	LOGL(<< "Loaded Controllable Object Script");
}

void Script::onUnload() {

	LOGL(<< "Unloaded Controllable Object Script");
}

void Script::exec(const Exec_I* port) {
	const F64 speed = SIM_HOOK.delta_time * (*di_move_speed->GET_DATA(F64));
	const F64_V2 last_obj_pos = obj_pos;
	if (SIM_HOOK.input_down["A"]) {
		obj_pos.x -= speed;
	}
	if (SIM_HOOK.input_down["D"]) {
		obj_pos.x += speed;
	}
	if (SIM_HOOK.input_down["W"]) {
		obj_pos.y += speed;
	}
	if (SIM_HOOK.input_down["S"]) {
		obj_pos.y -= speed;
	}

	obj_vel = obj_pos - last_obj_pos;

	render();
	eo_exec->exec();
}

void Script::render() {
	Color u_color = out_color;

	if (SIM_HOOK.input_down["5"]) {
		u_color = Color(1, 1, 0, 1);
	}
	else if (SIM_HOOK.input_down["6"]) {
		u_color = Color(0, 1, 1, 1);
	}
	else if (SIM_HOOK.input_down["7"]) {
		u_color = Color(1, 0, 1, 1);
	}
	/* Car Render
	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(60, 60), obj_pos + F32_V2(-60, 60), 4, u_color);

	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(  60, 60), obj_pos + F32_V2( 100, 20), 4, u_color);
	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2( -60, 60), obj_pos + F32_V2(-100, 20), 4, u_color);

	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2( 100, 20), obj_pos + F32_V2( 160, 10), 4, u_color);
	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(-100, 20), obj_pos + F32_V2(-160, 10), 4, u_color);

	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2( 160, 10), obj_pos + F32_V2( 170, -40), 4, u_color);
	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(-160, 10), obj_pos + F32_V2(-170, -40), 4, u_color);

	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2( 170, -40), obj_pos + F32_V2( 130, -40), 4, u_color);
	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(-170, -40), obj_pos + F32_V2(-130, -40), 4, u_color);

	RENDER::Dim_2D::RoundedLine(obj_pos + F32_V2(30, -40), obj_pos + F32_V2(-30, -40), 4, u_color);

	RENDER::Dim_2D::Circle(obj_pos + F32_V2( 80, -40), 40, u_color);
	RENDER::Dim_2D::Circle(obj_pos + F32_V2(-80, -40), 40, u_color);
	*/
	RENDER::Dim_2D::Circle(obj_pos, obj_rad, u_color);
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	if (port == do_obj_pos.get()) {
		return make_shared<Variable>(obj_pos);
	}
	if (port == do_obj_vel.get()) {
		return make_shared<Variable>(obj_vel);
	}
	return make_shared<Variable>(obj_rad);
}