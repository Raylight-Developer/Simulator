#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Background : Node {
			PORT_EXEC_I ei_exec;
			PORT_DATA_I di_color;

			PORT_EXEC_O eo_exec;

			Background();

			void exec(const Port* port) override;
		};
	}
}