#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_3D {
			struct Sphere : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_center;
				PORT_DATA_I di_radius;
				PORT_DATA_I di_color;

				PORT_EXEC_O eo_exec;

				Sphere();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}