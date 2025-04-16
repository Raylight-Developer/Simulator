#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Background : Node {
			Ptr_U<PORT::Exec_I> exec_in;
			Ptr_U<PORT::Exec_O> exec_out;

			Ptr_U<PORT::Data_I> color_in;

			Background();

			void exec(const Port* port) override;
		};
	}
}