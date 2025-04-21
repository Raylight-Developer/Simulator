#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct If_Else : Node {
			PORT_EXEC_I in;
			PORT_DATA_I condition;
			PORT_EXEC_O out_a;
			PORT_EXEC_O out_b;

			If_Else();

			void exec(const Port* port) override;
		};
	}
}