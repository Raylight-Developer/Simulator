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

				GUI::Options* var_type;

				Size();
				
				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}