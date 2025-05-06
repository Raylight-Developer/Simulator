#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Modify : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_list;
				PORT_DATA_I di_index;
				PORT_DATA_I di_value;

				PORT_EXEC_O eo_exec;

				GUI::Options* var_type;

				Modify();

				void exec(const Port* port) override;
			};
		}
	}
}