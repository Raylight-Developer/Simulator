#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Triangle : Node {
				PORT_EXEC_I exec_in;
				PORT_EXEC_O exec_out;

				PORT_DATA_I vert_a;
				PORT_DATA_I vert_b;
				PORT_DATA_I vert_c;
				PORT_DATA_I color;

				Triangle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}