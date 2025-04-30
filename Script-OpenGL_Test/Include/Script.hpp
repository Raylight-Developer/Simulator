#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I exec_in;
	PORT_DATA_I move_speed;

	PORT_EXEC_O exec_out;

	Color out_color;
	F32_V2 car_pos;

	Script(Session* session);

	void onLoad() override;
	void onUnload() override;

	void exec(const Exec_I* port) override;

	void render();
};