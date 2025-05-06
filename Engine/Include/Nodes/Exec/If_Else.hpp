#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct If_Else : Node {
			PORT_EXEC_I ei_exec;
			PORT_DATA_I di_cond;

			PORT_EXEC_O eo_true;
			PORT_EXEC_O eo_false;

			If_Else();

			void exec(const Port* port) override;
		};
	}
}