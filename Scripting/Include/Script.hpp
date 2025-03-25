#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script(Session* session);
	// Warning: Do not utilize. all cleanup should be handled by onUnload()
	~Script() {}

	void onLoad() override;
	void onUnload() override;

	void exec(const Port* port) override;
	Variable getData(const Port* port) const override;
};