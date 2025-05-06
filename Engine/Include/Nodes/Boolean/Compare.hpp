#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace BOOLEAN {
		struct Compare : Node {
			PORT_DATA_I di_a;
			PORT_DATA_I di_b;

			PORT_DATA_O do_res;

			GUI::Options* enums;

			Compare();

			Ptr_S<Variable> getData(const Port* port) override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}