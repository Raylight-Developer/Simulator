#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Key : Node {
				Key();
				PORT_DATA_O key;
				PORT_DATA_O is_down;

				Variable getData(const Port* port) const override;
			};
		}
	}
}