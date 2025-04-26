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

			void h_setVar(const QString name);
			void setVar(const QString name);

			Ptr_S<Variable> getData(const Port* port) override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				Ptr_S<Get> node;
				QString from, to;

				Set_Variable(Ptr_S<Get> node, const QString& from, const QString& to);

				void execute() const final override;
				void undo() final override;
			};
		};
	}
}