#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace BREAK {
			struct Vec2 : Node {
				PORT_DATA_I di_val;

				PORT_DATA_O do_x;
				PORT_DATA_O do_y;

				Vec2();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}