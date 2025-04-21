#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct Subsample : Node {
			I64 calls;
			PORT_EXEC_I exec_in;
			PORT_DATA_I delta_in;
			PORT_DATA_I count_in;

			PORT_EXEC_O exec_out;
			PORT_EXEC_O samples_out;
			PORT_DATA_O o_delta;
			PORT_DATA_O o_calls;
			PORT_DATA_O o_runtime;

			Subsample();

			void exec(const Port* port) override;
			Variable getData(const Port* port) const override;
		};
	}
}