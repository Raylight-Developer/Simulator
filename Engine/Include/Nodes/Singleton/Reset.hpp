#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace SINGLETON {
		struct Reset : Node {
			PORT_EXEC_O eo_exec;
			PORT_DATA_O do_bool;

			Reset();

			void exec();
			Ptr_S<Variable> getData(const Port* port) override;
			
			void loadDetail(const Token_Array& tokens) override;
		};
	}
}