#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLE {
		struct Constant : Node {
			PORT_DATA_O out;

			CORE::Stack<GUI::Graphics_Widget*> proxies;
			GUI::Options* var_type;
			QRectF expanded;
			Variable value;

			VAR_TYPE current_var_type;

			Constant();

			Ptr_S<Variable> getData(const Port* port) override;

			struct Set_Type : Self<Set_Type>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
			struct Set_Value : Self<Set_Value>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}