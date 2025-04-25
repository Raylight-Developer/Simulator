#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Size : Node {
				PORT_DATA_I list;

				PORT_DATA_O size;

				//Size();
				//
				//const Ptr_S<Variable> getData(const Port* port) const override;
			};
		}
	}
}