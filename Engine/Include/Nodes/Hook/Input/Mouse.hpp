#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		namespace INPUT {
			struct Mouse : Node {
				PORT_DATA_O do_is_down;

				GUI::Options* buttons;

				string button;

				Mouse();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}