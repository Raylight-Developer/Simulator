#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Access : Node {
				PORT_DATA_I list;
				PORT_DATA_I index;

				PORT_DATA_O value;

				Access();

				const Ptr_S<Variable> getData(const Port* port) const override;
			};
		}
	}
}