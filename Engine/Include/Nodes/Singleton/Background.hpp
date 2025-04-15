#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Background : Node {
			PORT:: Exec_I* exec_in;
			PORT:: Exec_O* exec_out;

			PORT:: Data_I* color_in;

			Background();

			void exec(const Port* port) override;
		};
	}
}