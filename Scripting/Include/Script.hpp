#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	Script(Session* session);

	/*
	Called Once after internally binding the script to the program, either after adding node to scene or during File::loadBuild().
	*/
	void onLoad() override;

	/*
	Called Once before the script is destroyed, either during program shutdown or manual unloading.
	
	WARNING: All resource and memory cleanup should be handled here, not in a destructor.
	*/
	void onUnload() override;

	/* OPTIONAL
	Handles node execution on trigger of const Exec_I* port.
	User should manually handle downstream Exec_Output execution from here, otherwise call a slightly more expensive: execAllDownstream().
	*/
	void exec(const Exec_I* port) override;

	/* OPTIONAL
	Handles data request by the connection of the const Data_O* port.
	*/
	Ptr_S<Variable> getData(const Data_O* port) override;
};