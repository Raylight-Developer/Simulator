#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Rectangle : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* vert_a;
				PORT::Data_I* vert_b;
				PORT::Data_I* vert_c;
				PORT::Data_I* vert_d;
				PORT::Data_I* color;

				Rectangle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}