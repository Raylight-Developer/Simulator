#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse_Wheel : Node {
				PORT_DATA_O do_angle_x;
				PORT_DATA_O do_angle_y;

				Mouse_Wheel();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}