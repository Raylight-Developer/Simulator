#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Vec4 : Node {
				PORT_DATA_I di_x;
				PORT_DATA_I di_y;
				PORT_DATA_I di_z;
				PORT_DATA_I di_w;

				PORT_DATA_O do_val;

				Vec4();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}