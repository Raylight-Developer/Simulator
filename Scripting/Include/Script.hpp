#pragma once

#include "Script_Include.hpp"

class Script : public CORE::Script {
public:
	void onLoad() override;
	void onUnload() override;
};