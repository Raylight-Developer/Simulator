#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Euler_Tick : Node {
			PORT_EXEC_O eo_exec;
			PORT_DATA_O do_delta;
			PORT_DATA_O do_calls;
			PORT_DATA_O do_runtime;

			F64 delta;
			F64 runtime;

			Euler_Tick();

			void exec(const F64& delta);

			Ptr_S<Variable> getData(const Port* port) override;

			void loadDetail(const Token_Array& tokens) override;
		};
	}
}