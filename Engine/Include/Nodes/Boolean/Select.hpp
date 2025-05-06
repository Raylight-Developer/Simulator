#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace BOOLEAN {
		struct Select : Node {
			PORT_DATA_I di_cond;
			PORT_DATA_I di_true;
			PORT_DATA_I di_false;

			PORT_DATA_O do_res;

			Select();

			Ptr_S<Variable> getData(const Port* port) override;
		};
	}
}