#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Insert : Node {
				PORT_EXEC_I ei_exec;
				PORT_DATA_I di_list;
				PORT_DATA_I di_index;
				PORT_DATA_I di_value;

				PORT_EXEC_O eo_exec;
				PORT_DATA_O do_list_pass;

				Insert();

				GUI::Options* var_type;

				void exec(const Port* port) override;
				Ptr_S<Variable> getData(const Port* port) override;

				void saveDetail(CORE::Lace& lace) const override;
				void loadDetail(const Token_Array& tokens) override;
			};
		}
	}
}