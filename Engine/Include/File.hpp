#pragma once

#include "KL.hpp"

#include "Nodes.hpp"

struct File {
	NODES::DEFAULT::Euler_Tick*  euler_tick;
	NODES::DEFAULT::Background*  background;
	NODES::DEFAULT::Camera_2D*   camera_2d;
	NODES::DEFAULT::Camera_3D*   camera_3d;
	NODES::DEFAULT::Input_Key*   input_key;
	NODES::DEFAULT::Input_Mouse* input_mouse;

	File();
};