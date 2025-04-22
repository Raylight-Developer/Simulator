#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script(Session* session);

	/*
	Called Once after internally binding the script to the program.
	*/
	void onLoad() override;

	/*
	Called Once before the script is destroyed, either during program shutdown or manual unloading.
	
	WARNING: All resource and memory cleanup should be handled here, not in a destructor.
	*/
	void onUnload() override;

	/* OPTIONAL
	Handles node execution on Exec_Input trigger.
	User should manually handle downstream Exec_Output execution from here.
	*/
	void exec(const Port* port) override;

	/* OPTIONAL
	Handles data request by the Data_Output ports.
	*/
	Variable getData(const Port* port) const override;
};