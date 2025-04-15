#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct Subsample : Node {
			F64 delta;
			PORT::Exec_I* exec_in;
			PORT::Data_I* count_in;

			PORT::Exec_O* exec_out;
			PORT::Data_O* o_delta;
			PORT::Data_O* o_calls;
			PORT::Data_O* o_runtime;

			GUI::Int_Input* count;

			Subsample();

			void exec(const Port* port) override;
			Variable getData(const Port* port) const override;
		};
	}
}