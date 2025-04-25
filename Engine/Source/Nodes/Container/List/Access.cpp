#include "Nodes/Container/List/Access.hpp"

NODES::CONTAINER::LIST::Access::Access() {
}

const Ptr_S<Variable> NODES::CONTAINER::LIST::Access::getData(const Port* port) const {
	return list->getData();
}