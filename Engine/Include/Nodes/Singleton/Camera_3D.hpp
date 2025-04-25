#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Camera_3D : Node {
			PORT_EXEC_I exec_in;
			PORT_EXEC_O exec_out;

			Camera_3D();

			void exec(const Port* port) override;
		};
	}
}