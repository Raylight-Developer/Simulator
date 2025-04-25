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

				GUI::Options* var_type;

				Access();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}