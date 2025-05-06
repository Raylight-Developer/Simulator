#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Clear : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_list;

				PORT_EXEC_O eo_exec;
				PORT_DATA_O do_list_pass;

				Clear();

				GUI::Options* var_type;

				void exec(const Port* port) override;
				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}