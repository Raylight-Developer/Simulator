#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_EXEC_O eo_exec;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
};