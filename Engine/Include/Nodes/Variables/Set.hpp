#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLE {
		struct Set : Node {
			PORT_EXEC_I ei_exec;
			PORT_DATA_I di_value;

			PORT_EXEC_O eo_exec;
			PORT_DATA_O do_value_pass;

			GUI::Graphics_Widget* proxy_label;
			GUI::Label* label;
			QString var;

			Set();

			void h_setVar(const QString name);
			void setVar(const QString name);

			void exec(const Port* port) override;
			Ptr_S<Variable> getData(const Port* port) override;

			void saveDetail(CORE::Lace& lace) const override;
			void loadDetail(const Token_Array& tokens) override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				Ptr_S<Set> node;
				QString from, to;

				Set_Variable(Ptr_S<Set> node, const QString& from, const QString& to);

				void execute() const final override;
				void undo() final override;
			};
		};
	}
}