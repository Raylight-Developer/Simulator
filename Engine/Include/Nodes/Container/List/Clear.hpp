#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Clear : Node {
				PORT_EXEC_I call;
				PORT_DATA_I list;

				PORT_EXEC_O call_pass;
				PORT_DATA_O list_pass;

				Clear();

				GUI::Options* var_type;

				void exec(const Port* port) override;
				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}