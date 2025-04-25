#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Reset : Node {
			PORT_EXEC_O exec_out;
			PORT_DATA_O bool_out;

			Reset();

			void exec();
			Ptr_S<Variable> getData(const Port* port) override;

			void loadDetail() override;
		};
	}
}