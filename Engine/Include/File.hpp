#pragma once

#include "KL.hpp"

#include "Nodes.hpp"

struct File {
	NODES::SINGLETON::Euler_Tick* euler_tick;
	
	KL::List<Node*> nodes;

	File();
};