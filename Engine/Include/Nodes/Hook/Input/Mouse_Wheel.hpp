#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse_Wheel : Node {
				Mouse_Wheel();
				PORT_DATA_O angle_x;
				PORT_DATA_O angle_y;

				Variable getData(const Port* port) const override;
			};
		}
	}
}