#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script();
	~Script();

	void exec(const Port* port) override;
	Variable getData(const Port* port) const override;
};