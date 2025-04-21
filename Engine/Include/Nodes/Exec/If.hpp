#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct If : Node {
			PORT_EXEC_I in;
			PORT_DATA_I condition;
			PORT_EXEC_O out;

			If();

			void exec(const Port* port) override;
		};
	}
}