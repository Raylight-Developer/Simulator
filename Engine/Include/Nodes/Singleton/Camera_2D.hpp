#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Camera_2D : Node {
			PORT_EXEC_I ei_exec;
			PORT_DATA_I di_center;
			PORT_DATA_I di_zoom;

			PORT_EXEC_O eo_exec;

			Camera_2D();

			void exec(const Port* port) override;
		};
	}
}