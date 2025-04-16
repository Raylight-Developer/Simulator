#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace RENDERING {
		namespace DIM_2D {
			struct Rectangle : Node {
				Ptr_U<PORT::Exec_I> exec_in;
				Ptr_U<PORT::Exec_O> exec_out;

				Ptr_U<PORT::Data_I> vert_a;
				Ptr_U<PORT::Data_I> vert_b;
				Ptr_U<PORT::Data_I> vert_c;
				Ptr_U<PORT::Data_I> vert_d;
				Ptr_U<PORT::Data_I> color;

				Rectangle();

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}