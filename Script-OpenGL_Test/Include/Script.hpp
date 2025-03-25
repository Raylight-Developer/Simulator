#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script(Session* session);

	void onLoad() override;
	void onUnload() override;

	void exec(const Port* port) override;

	Exec_I* exec_in;
	Exec_O* exec_out;

	void render();
};