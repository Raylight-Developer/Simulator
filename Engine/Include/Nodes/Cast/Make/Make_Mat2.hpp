#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Mat2 : Node {
				PORT_DATA_I di_col_x;
				PORT_DATA_I di_col_y;

				PORT_DATA_O do_val;

				Mat2();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}