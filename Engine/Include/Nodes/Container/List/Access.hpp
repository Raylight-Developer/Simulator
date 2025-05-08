#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace CONTAINER {
		namespace LIST {
			struct Access : Node {
				PORT_DATA_I di_list;
				PORT_DATA_I di_index;

				PORT_DATA_O do_value;
				PORT_DATA_O do_index_pass;

				GUI::Options* var_type;

				Access();

				Ptr_S<Variable> getData(const Port* port) override;

				void saveDetail(CORE::Lace& lace) const override;
				void loadDetail(const Token_Array& tokens) override;
			};
		}
	}
}