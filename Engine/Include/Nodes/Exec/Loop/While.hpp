#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		namespace LOOP {
			struct While : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_cond;

				PORT_EXEC_O eo_finished;
				PORT_EXEC_O eo_while;

				While();

				void exec(const Port* port) override;
			};
		}
	}
}