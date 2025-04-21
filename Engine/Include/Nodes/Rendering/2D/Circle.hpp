#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Circle : Node {
				PORT_EXEC_I exec_in;
				PORT_EXEC_O exec_out;

				PORT_DATA_I center;
				PORT_DATA_I radius;
				PORT_DATA_I color;

				Circle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}