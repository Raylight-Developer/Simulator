#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;
};