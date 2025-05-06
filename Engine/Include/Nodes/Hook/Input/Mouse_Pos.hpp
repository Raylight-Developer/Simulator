#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse_Pos : Node {
				PORT_DATA_O do_screen_pos;
				PORT_DATA_O do_is_on_screen;

				Mouse_Pos();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}