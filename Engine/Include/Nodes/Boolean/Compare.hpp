#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace BOOLEAN {
		struct Compare : Node {
			PORT_DATA_I in_a;
			PORT_DATA_I in_b;
			PORT_DATA_O out;

			GUI::Options* enums;

			Compare();

			bool onConnRequested(Port* port, Connection* conn);
			void onDisconnection(Port* port);
			void cascade(Port* port, const VAR_TYPE& var_type);

			Variable getData(const Port* port) const override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
	}
}