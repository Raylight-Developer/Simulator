#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		struct Display : Node {
			Display();
			PORT_DATA_O resolution;

			const Ptr_S<Variable> getData(const Port* port) const override;
		};
	}
}