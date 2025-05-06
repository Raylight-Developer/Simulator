#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Key : Node {
				PORT_DATA_O do_is_down;

				GUI::Options* keys;

				string key;

				Key();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}