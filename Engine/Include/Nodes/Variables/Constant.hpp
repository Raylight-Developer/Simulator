#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLE {
		struct Constant : Node {
			PORT_DATA_O out;

			CORE::Stack<GUI::Graphics_Widget*> proxies;
			GUI::Graphics_Widget* proxy_var_type;
			GUI::Options* var_type;
			QRectF expanded;
			Variable value;

			VAR_TYPE current_var_type;

			Constant();

			Ptr_S<Variable> getData(const Port* port) override;

			void saveDetail(CORE::Lace& lace) const override;
			void loadDetail(const Token_Array& tokens) override;

			void h_setType(const VAR_TYPE& type);
			void setType(const VAR_TYPE& type);

			void h_setValue(const Variable& variable);
			void setValue(const Variable& variable);

			struct Set_Type : Self<Set_Type>, CORE::CMD {
				Ptr_S<Constant> node;
				VAR_TYPE from, to;
				Variable from_val;

				Set_Type(Ptr_S<Constant> node, const VAR_TYPE& from, const VAR_TYPE& to, const Variable& from_val);

				void execute() const final override;
				void undo() final override;
			};

			struct Set_Value : Self<Set_Value>, CORE::CMD {
				Ptr_S<Constant> node;
				Variable from, to;

				Set_Value(Ptr_S<Constant> node, const Variable& from, const Variable& to);

				void execute() const final override;
				void undo() final override;
			};
		};
	}
}