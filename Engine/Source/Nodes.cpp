#include "Nodes.hpp"

NODE::NODES::ARITHMETIC::Template::Template() :
	allowed_types({ VARIABLE_INTEGRALS })
{
	var_type = VARIABLE::Type::NONE;
	i_a = new PORT::Data_I(this, "A");
	i_b = new PORT::Data_I(this, "B");
	out = new PORT::Data_O(this, "RES");

	i_a->conn_request = std::bind(&Template::call_connRequestI, this, nullptr, nullptr);
	i_b->conn_request = std::bind(&Template::call_connRequestI, this, nullptr, nullptr);
	out->conn_request = std::bind(&Template::call_connRequestO, this, nullptr, nullptr);
}

void NODE::NODES::ARITHMETIC::Template::setType(const VARIABLE::Type& type) {
	var_type = type;
	i_a->setType(type);
	i_b->setType(type);
	out->setType(type);
}

bool NODE::NODES::ARITHMETIC::Template::call_connRequestI(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = conn->getDataO()->var_type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			setType(incoming_type);
			return true;
		}
		else if (var_type == incoming_type) {
			return true;
		}
	}
	return false;
}

bool NODE::NODES::ARITHMETIC::Template::call_connRequestO(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = conn->getDataI()->var_type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			setType(incoming_type);
			return true;
		}
		else if (var_type == incoming_type) {
			return true;
		}
	}
	return false;
}

void NODE::NODES::ARITHMETIC::Template::call_disconnection(Port* port, Connection* conn) {
	if (not i_a->connected() and not i_b->connected() and not out->connected()) {
		setType(VARIABLE::Type::NONE);
	}
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

NODE::NODES::TRIGONOMETRY::Template::Template() {
	in = new PORT::Data_I(this, "IN");
	out = new PORT::Data_O(this, "OUT");

	in->conn_request = std::bind(&Template::call_connRequest, this, nullptr, nullptr);
	out->conn_request = std::bind(&Template::call_connRequest, this, nullptr, nullptr);

	enums = new GUI::Options(); // TODO delete
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });
}

bool NODE::NODES::TRIGONOMETRY::Template::call_connRequest(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = (port == in) ? conn->getDataO()->var_type : (port == out) ? conn->getDataI()->var_type : VARIABLE::Type::NONE;
	if (incoming_type == VARIABLE::Type::FLOAT) {
		return true;
	}
	return false;
}

Variable NODE::NODES::TRIGONOMETRY::Template::getData(const Port* port) const {
	const dvec1 x = in->getData().get<dvec1>();
	switch (enums->currentIndex()) {
		case  0: return sin(x);
		case  1: return cos(x);
		case  2: return tan(x);
		case  3: return asin(x);
		case  4: return acos(x);
		case  5: return atan(x);
		case  6: return sinh(x);
		case  7: return cosh(x);
		case  8: return tanh(x);
		case  9: return 1.0 / tan(x);
		case 10: return 1.0 / cos(x);
		case 11: return 1.0 / sin(x);
		case 12: return cosh(x) / sinh(x);
		case 13: return 1.0 / cosh(x);
		case 14: return 1.0 / sinh(x);
	}
	return Variable(x);
}