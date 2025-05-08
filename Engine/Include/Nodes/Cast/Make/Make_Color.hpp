#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Color : Node {
				PORT_DATA_I di_r;
				PORT_DATA_I di_g;
				PORT_DATA_I di_b;
				PORT_DATA_I di_a;

				PORT_DATA_O do_val;

				Color();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}