#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Key : Node {
				Key();
				string key;
				PORT_DATA_O is_down;

				GUI::Options* keys;

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}