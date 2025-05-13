#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_DATA_I di_move_speed;

	PORT_EXEC_O eo_exec;

	Color out_color;
	F32_V2 car_pos;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;

	void render();
};