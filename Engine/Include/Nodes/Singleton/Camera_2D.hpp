#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Camera_2D : Node {
			PORT_EXEC_I exec_in;
			PORT_EXEC_O exec_out;

			PORT_DATA_I center;
			PORT_DATA_I zoom;

			Camera_2D();

			void exec(const Port* port) override;
		};
	}
}