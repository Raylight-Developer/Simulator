#pragma once

#include "Script_Include.hpp"

F64_V2 randomUnitVector();
void circleDynamicCollision(F64_V2& pos_a, F64_V2& pos_b, F64_V2& vel_a, F64_V2& vel_b, const F64& rad_a, const F64& rad_b, const F64& mass_a, const F64& mass_b, const F64& restitution);
void circleStaticCollision(F64_V2& pos_a, const F64_V2& pos_b, F64_V2& vel_a, const F64_V2& vel_b, const F64& rad_a, const F64& rad_b, const F64& mass_a, const F64& mass_b, const F64& restitution);

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_DATA_I di_effector_pos;
	PORT_DATA_I di_effector_vel;
	PORT_DATA_I di_effector_rad;

	PORT_EXEC_O eo_exec;

	CORE::Stack<F64_V2> positions;
	CORE::Stack<F64_V2> velocities;
	F64_V2 gravity;
	F64 restitution;
	F64 terminal;
	F64 radius;
	U32 count;
	U32 samples;

	F64_V2 x_bounds;
	F64_V2 y_bounds;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
};