#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Circle : Node {
				Ptr_U<PORT::Exec_I> exec_in;
				Ptr_U<PORT::Exec_O> exec_out;

				Ptr_U<PORT::Data_I> center;
				Ptr_U<PORT::Data_I> radius;
				Ptr_U<PORT::Data_I> color;

				Circle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}