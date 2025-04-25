#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace MATH {
		struct Arithmetic : Node {
			PORT_DATA_I i_a;
			PORT_DATA_I i_b;
			PORT_DATA_O out;

			GUI::Options* enums;

			Arithmetic();

			const Ptr_S<Variable> getData(const Port* port) const override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}