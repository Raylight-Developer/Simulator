#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Quat : Node {
				PORT_DATA_I di_w;
				PORT_DATA_I di_x;
				PORT_DATA_I di_y;
				PORT_DATA_I di_z;

				PORT_DATA_O do_val;

				Quat();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}