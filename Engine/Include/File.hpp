#pragma once

#include "KL.hpp"

#include "Nodes.hpp"

struct File {
	KL::Observable_Ptr<NODES::EXEC::Euler_Tick> tick;

	File();
};