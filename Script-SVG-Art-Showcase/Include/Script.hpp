#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_DATA_I di_resolution;
	PORT_DATA_I di_line_width;
	PORT_DATA_I di_path;

	PORT_EXEC_O eo_exec;

	string last_path;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
};

F32_V2 cubicBezier(const F32_V2& p0, const F32_V2& p1, const F32_V2& p2, const F32_V2& p3, const F32& t);