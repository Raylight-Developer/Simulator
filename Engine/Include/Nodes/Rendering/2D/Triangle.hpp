#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Triangle : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_vert_a;
				PORT_DATA_I di_vert_b;
				PORT_DATA_I di_vert_c;
				PORT_DATA_I di_color;

				PORT_EXEC_O eo_exec;

				Triangle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}