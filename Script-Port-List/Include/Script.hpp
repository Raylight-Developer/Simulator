#pragma once

#include "Script_Include.hpp"

struct Script : SCRIPT {
	PORT_EXEC_O di_x;

	PORT_DATA_O di_a;
	PORT_DATA_O di_b;
	PORT_DATA_O di_c;
	PORT_DATA_O di_d;
	PORT_DATA_O di_e;
	PORT_DATA_O di_f;
	PORT_DATA_O di_g;
	PORT_DATA_O di_h;
	PORT_DATA_O di_i;
	PORT_DATA_O di_j;
	PORT_DATA_O di_k;
	PORT_DATA_O di_l;

	Script(Session* session);

	/*
	Called Once after internally binding the script to the program, either after adding node to scene or during File::loadBuild().
	*/
	void onLoad() final override;

	/*
	Called Once before the script is destroyed, either during program shutdown or manual unloading.
	
	WARNING: All resource and memory cleanup should be handled here, not in a destructor.
	*/
	void onUnload() final override;

	/* OPTIONAL
	Handles node execution on trigger of const Exec_I* port.
	User should manually handle downstream Exec_Output execution from here, otherwise call a minimally more expensive but automatic: execAllDownstream().
	*/
	void exec(const Exec_I* port) final override;

	/* OPTIONAL
	Handles data request by the connection of the const Data_O* port.
	*/
	Ptr_S<Variable> getData(const Data_O* port) final override;
};