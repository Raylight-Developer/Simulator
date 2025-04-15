#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Euler_Tick : Node {
			F64 delta;
			PORT::Exec_O* exec_out;
			PORT::Data_O* o_delta;
			PORT::Data_O* o_calls;
			PORT::Data_O* o_runtime;

			Euler_Tick();

			void exec(const F64& delta);
			Variable getData(const Port* port) const override;
		};
	}
}