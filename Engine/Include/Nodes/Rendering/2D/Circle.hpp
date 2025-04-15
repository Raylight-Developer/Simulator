#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Circle : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* center;
				PORT::Data_I* radius;
				PORT::Data_I* color;

				Circle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}