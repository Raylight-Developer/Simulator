#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;

	PORT_EXEC_O eo_exec;

	CORE::Stack<F64_V2> positions;
	CORE::Stack<F64_V2> velocities;
	F64_V2 gravity;
	F64 restitution;
	F64 terminal;
	F64 radius;
	U32 count;

	F64_V2 x_bounds;
	F64_V2 y_bounds;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
	Ptr_S<Variable> getData(const Data_O* port) final override;
};