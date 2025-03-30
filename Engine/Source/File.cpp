#include "File.hpp"

File::File() {
	euler_tick = new NODES::SINGLETON::Euler_Tick();
	nodes.push(euler_tick);
}