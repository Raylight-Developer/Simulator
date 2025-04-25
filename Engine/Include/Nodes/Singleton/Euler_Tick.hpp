#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Euler_Tick : Node {
			F64 delta;
			PORT_EXEC_O exec_out;
			PORT_DATA_O o_delta;
			PORT_DATA_O o_calls;
			PORT_DATA_O o_runtime;

			Euler_Tick();

			void exec(const F64& delta);

			const Ptr_S<Variable> getData(const Port* port) const override;
			void loadDetail() override;
		};
	}
}