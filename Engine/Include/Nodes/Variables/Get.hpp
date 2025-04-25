#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLE {
		struct Get : Node {
			PORT_DATA_O out;
			GUI::Label* label;
			QString var;

			Get();
			void setVar(const QString name);

			const Ptr_S<Variable> getData(const Port* port) const override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}