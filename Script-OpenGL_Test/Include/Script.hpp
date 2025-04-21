#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I exec_in;
	PORT_EXEC_O exec_out;

	Script(Session* session);

	void onLoad() override;
	void onUnload() override;

	void exec(const Port* port) override;

	void render();
};