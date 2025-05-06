#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;

	PORT_EXEC_O eo_exec;

	bool panning;
	F64_V2 last_pos;

	Script(Session* session);

	void onLoad() override;
	void onUnload() override;

	void exec(const Exec_I* port) override;
	Ptr_S<Variable> getData(const Data_O* port) override;
};