#pragma once

#include "Script_Include.hpp"

#include "Boids.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_DATA_I di_runtime;
	PORT_DATA_I di_path_size;
	PORT_DATA_I di_path_weight;

	PORT_EXEC_O eo_exec;

	bool initialized;

	BoidSystem boid_system;

	U32 count;
	U32 samples;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
};