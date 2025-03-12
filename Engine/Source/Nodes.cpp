#include "Nodes.hpp"

NODE::NODES::ARITHMETIC::Template::Template() :
	allowed_types({ VARIABLE_INTEGRALS })
{
	var_type = VARIABLE::Type::NONE;
	i_a = new PORT::Data_I(this, "A");
	i_b = new PORT::Data_I(this, "B");
	o   = new PORT::Data_O(this, "RES");

	i_a->conn_request = std::bind(&Template::connRequestI, this, nullptr);
	i_b->conn_request = std::bind(&Template::connRequestI, this, nullptr);
	o  ->conn_request = std::bind(&Template::connRequestO, this, nullptr);
}

bool NODE::NODES::ARITHMETIC::Template::connRequestI(Connection* conn) {
	const VARIABLE::Type& incoming_type = conn->getDataO()->type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			var_type = incoming_type;
			return true;
		}
		else if (var_type == incoming_type) {
			return true;
		}
	}
	return false;
}

bool NODE::NODES::ARITHMETIC::Template::connRequestO(Connection* conn) {
	const VARIABLE::Type& incoming_type = conn->getDataI()->type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			var_type = incoming_type;
			return true;
		}
		else if (var_type == incoming_type) {
			return true;
		}
	}
	return false;
}

Variable NODE::NODES::ARITHMETIC::Add::getData(const Port* port) const {
	return i_a->getData() + i_b->getData();
}

Variable NODE::NODES::ARITHMETIC::Sub::getData(const Port* port) const {
	return i_a->getData() - i_b->getData();
}

Variable NODE::NODES::ARITHMETIC::Mul::getData(const Port* port) const {
	return i_a->getData() * i_b->getData();
}

Variable NODE::NODES::ARITHMETIC::Div::getData(const Port* port) const {
	return i_a->getData() / i_b->getData();
}