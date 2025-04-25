#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Clear : Node {
				PORT_EXEC_I exec;
				PORT_DATA_I list;

				PORT_DATA_I list_pass;

				//Clear();
				//
				//void exec(const Port* port) override;
				//const Ptr_S<Variable> getData(const Port* port) const override;
			};
		}
	}
}