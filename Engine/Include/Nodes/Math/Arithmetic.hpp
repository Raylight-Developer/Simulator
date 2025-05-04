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

			Ptr_S<Variable> getData(const Port* port) override;

			void saveDetail(CORE::Lace& lace) const override;
			void loadDetail(const Token_Array& tokens) override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}