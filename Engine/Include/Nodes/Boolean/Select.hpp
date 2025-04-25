#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace BOOLEAN {
		struct Select : Node {
			PORT_DATA_I condition;
			PORT_DATA_I i_true;
			PORT_DATA_I i_false;
			PORT_DATA_O out;

			Select();

			const Ptr_S<Variable> getData(const Port* port) const override;
		};
	}
}