#include "Nodes.hpp"

NODE::NODES::Arithmetic::Arithmetic() :
	NODE::Node("Arithmetic"),
	allowed_types({ VARIABLE_INTEGRALS })
{
	rect.setWidth(100);
	rect.setHeight(80);

	i_a = new PORT::Data_I(this, "A");
	i_b = new PORT::Data_I(this, "B");
	out = new PORT::Data_O(this, "O");

	i_a->connRequested = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };
	i_b->connRequested = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };
	out->connRequested = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };
	i_a->disconnection = [this](Port* port){ call_disconnection(port); };
	i_b->disconnection = [this](Port* port){ call_disconnection(port); };
	out->disconnection = [this](Port* port){ call_disconnection(port); };

	setType(VARIABLE::Type::NONE);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(40, 20);
	enums->addItems({ "+", "-", "*", "/" });

	QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(this);
	proxyWidget->setWidget(enums);
	proxyWidget->setPos(30, 30);
	proxyWidget->setFlag(QGraphicsItem::ItemIsMovable);
	proxyWidget->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void NODE::NODES::Arithmetic::setType(const VARIABLE::Type& type) {
	var_type = type;
	i_a->setType(type);
	i_b->setType(type);
	out->setType(type);
}

bool NODE::NODES::Arithmetic::call_connRequest(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = (port == out) ? conn->getDataI()->var_type : conn->getDataO()->var_type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			setType(incoming_type);
			conn->color = VARIABLE::toColor(incoming_type);
			return true;
		}
		else if (var_type == incoming_type) {
			return true;
		}
	}
	return false;
}

void NODE::NODES::Arithmetic::call_disconnection(Port* port) {
	if (not i_a->connected() and not i_b->connected() and not out->connected()) {
		setType(VARIABLE::Type::NONE);
	}
}

Variable NODE::NODES::Arithmetic::getData(const Port* port) const {
	switch (enums->currentIndex()) {
		case 0: return i_a->getData() + i_b->getData();
		case 1: return i_a->getData() - i_b->getData();
		case 2: return i_a->getData() * i_b->getData();
		case 3: return i_a->getData() / i_b->getData();
	}
	return Variable(0.0);
}

NODE::NODES::Trigonometry::Trigonometry() :
	NODE::Node("Trigonometry")
{
	rect.setWidth(140);
	rect.setHeight(60);

	in = new PORT::Data_I(this, "I", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "O", VARIABLE::Type::FLOAT);

	in->connRequested  = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };
	out->connRequested = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(80, 20);
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });

	QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(this);
	proxyWidget->setWidget(enums);
	proxyWidget->setPos(30, 30);
	proxyWidget->setFlag(QGraphicsItem::ItemIsMovable);
	proxyWidget->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

bool NODE::NODES::Trigonometry::call_connRequest(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = (port == out) ? conn->getDataI()->var_type : conn->getDataO()->var_type;
	if (incoming_type == VARIABLE::Type::FLOAT or incoming_type == VARIABLE::Type::NONE) {
		return true;
	}
	return false;
}

Variable NODE::NODES::Trigonometry::getData(const Port* port) const {
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