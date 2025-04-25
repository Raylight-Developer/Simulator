#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace MATH {
		struct Trigonometry : Node {
			PORT_DATA_I in;
			PORT_DATA_O out;

			GUI::Options* enums;

			Trigonometry();

			Ptr_S<Variable> getData(const Port* port) override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}