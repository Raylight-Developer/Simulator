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

				Variable getData(const Port* port) const override;
			};
		}
	}
}