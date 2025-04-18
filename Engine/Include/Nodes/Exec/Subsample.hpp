#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace EXEC {
		struct Subsample : Node {
			I64 calls;
			Ptr_U<PORT::Exec_I> exec_in;
			Ptr_U<PORT::Data_I> delta_in;
			Ptr_U<PORT::Data_I> count_in;

			Ptr_U<PORT::Exec_O> exec_out;
			Ptr_U<PORT::Exec_O> samples_out;
			Ptr_U<PORT::Data_O> o_delta;
			Ptr_U<PORT::Data_O> o_calls;
			Ptr_U<PORT::Data_O> o_runtime;

			Subsample();

			void exec(const Port* port) override;
			Variable getData(const Port* port) const override;
		};
	}
}