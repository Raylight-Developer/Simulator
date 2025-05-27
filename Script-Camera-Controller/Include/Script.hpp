#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;

	PORT_EXEC_O eo_exec;

	bool panning;
	F64_V2 last_pos;

	bool alt_pressed;
	bool mode_3d;
	bool orbiting;
	bool first_person;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
	Ptr_S<Variable> getData(const Data_O* port) final override;
};