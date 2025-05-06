#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		namespace LOOP {
			struct For : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_count;

				PORT_EXEC_O eo_finished;
				PORT_EXEC_O eo_for;
				PORT_DATA_O do_i;

				I64 for_i;

				For();

				void exec(const Port* port) override;
				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}