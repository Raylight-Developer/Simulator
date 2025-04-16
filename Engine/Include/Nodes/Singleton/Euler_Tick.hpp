#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Euler_Tick : Node {
			F64 delta;
			Ptr_U<PORT::Exec_O> exec_out;
			Ptr_U<PORT::Data_O> o_delta;
			Ptr_U<PORT::Data_O> o_calls;
			Ptr_U<PORT::Data_O> o_runtime;

			Euler_Tick();

			void exec(const F64& delta);
			Variable getData(const Port* port) const override;
		};
	}
}