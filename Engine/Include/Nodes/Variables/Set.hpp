#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLES {
		struct Set : Node {
			Ptr_U<PORT::Exec_I> exec_in;
			Ptr_U<PORT::Exec_O> exec_out;
			Ptr_U<PORT::Data_I> in;
			Ptr_U<PORT::Data_O> out;
			GUI::Label* label;
			QString var;

			Set();

			void h_setVar(const QString name);
			void setVar(const QString name);

			void exec(const Port* port) override;
			Variable getData(const Port* port) const override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				Set* node;
				QString from, to;

				Set_Variable(Set* node, const QString& from, const QString& to);

				void execute() const final override;
				void undo() final override;
			};
		};
	}
}