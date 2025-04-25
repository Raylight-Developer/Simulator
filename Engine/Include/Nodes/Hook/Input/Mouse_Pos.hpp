#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse_Pos : Node {
				Mouse_Pos();
				PORT_DATA_O screen_pos;
				PORT_DATA_O is_on_screen;

				const Ptr_S<Variable> getData(const Port* port) const override;
			};
		}
	}
}