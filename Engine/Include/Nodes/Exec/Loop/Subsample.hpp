#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		namespace LOOP{
			struct Subsample : Node {
				I64 calls;
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_delta;
				PORT_DATA_I di_count;

				PORT_EXEC_O eo_finished;
				PORT_EXEC_O eo_sample;
				PORT_DATA_O do_delta;
				PORT_DATA_O do_calls;
				PORT_DATA_O do_runtime;

				Subsample();

				void exec(const Port* port) override;
				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}