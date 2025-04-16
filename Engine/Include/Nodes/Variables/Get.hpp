#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLES {
		struct Get : Node {
			Ptr_U<PORT::Data_O> out;
			GUI::Label* label;
			QString var;

			Get();
			void setVar(const QString name);

			Variable getData(const Port* port) const override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}