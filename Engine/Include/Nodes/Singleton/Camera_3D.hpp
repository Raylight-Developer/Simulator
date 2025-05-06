#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Camera_3D : Node {
			PORT_EXEC_I ei_exec;

			PORT_EXEC_O eo_exec;

			Camera_3D();

			void exec(const Port* port) override;
		};
	}
}