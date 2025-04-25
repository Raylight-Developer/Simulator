#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse : Node {
				Mouse();
				string button;
				PORT_DATA_O is_down;

				GUI::Options* buttons;

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}