#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CAST {
		namespace CONVERT {
			struct I64_To_F64 : Node {
				PORT_DATA_I di_val;
				PORT_DATA_O do_res;

				I64_To_F64();

				Ptr_S<Variable> getData(const Port* port) override;
			};
		}
	}
}