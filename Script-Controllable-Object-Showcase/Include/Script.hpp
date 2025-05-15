#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_DATA_I di_move_speed;

	PORT_EXEC_O eo_exec;
	PORT_DATA_O do_obj_pos;
	PORT_DATA_O do_obj_vel;
	PORT_DATA_O do_obj_rad;

	Color out_color;
	F64_V2 obj_pos;
	F64_V2 obj_vel;
	F64 obj_rad;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
	Ptr_S<Variable> getData(const Data_O* port) final override;

	void render();
};