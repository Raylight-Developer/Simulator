#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Reset : Node {
			Ptr_U<PORT::Exec_O> exec_out;
			Ptr_U<PORT::Data_O> bool_out;

			Reset();

			void exec();
			Variable getData(const Port* port) const override;
		};
	}
}