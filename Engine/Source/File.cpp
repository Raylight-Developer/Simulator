#include "File.hpp"

File::File() {
	euler_tick  = new NODES::DEFAULT::Euler_Tick();
	background  = new NODES::DEFAULT::Background();
	camera_2d   = new NODES::DEFAULT::Camera_2D();
	camera_3d   = new NODES::DEFAULT::Camera_3D();
	input_key   = new NODES::DEFAULT::Input_Key();
	input_mouse = new NODES::DEFAULT::Input_Mouse();
}