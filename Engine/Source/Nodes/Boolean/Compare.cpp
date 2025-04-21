#include "Nodes/Boolean/Compare.hpp"

NODES::BOOLEAN::Compare::Compare() :
	Node("Compare")
{
	rect.setWidth(120);
	rect.setHeight(80);

	in_a = DATA_I("", VAR_TYPE::NONE);
	in_b = DATA_I("", VAR_TYPE::NONE);
	out  = DATA_O("", VAR_TYPE::BOOL);

	in_a->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_b->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	in_a->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_b->onDisconnection = [this](Port* port){ onDisconnection(port); };
	in_a->onTypeChanged   = [this](Port* port, const VAR_TYPE& var_type) { cascade(port, var_type); };
	in_b->onTypeChanged   = [this](Port* port, const VAR_TYPE& var_type) { cascade(port, var_type); };

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "==", "!=", ">", "<", ">=", "<=", "Sign"});

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

bool NODES::BOOLEAN::Compare::onConnRequested(Port* port, Connection* conn) {
	if (port == out.get()) {
		return true;
	}

	const VAR_TYPE incoming_type = conn->getDataO()->var_type;
	if (port == in_a.get()) {
		if (!in_b->connected()) {
			in_a->setType(incoming_type);
			in_b->setType(incoming_type);
			return true;
		}
		else if (in_b->var_type == incoming_type) {
			in_a->setType(incoming_type);
			return true;
		}
	}
	if (port == in_b.get()) {
		if (!in_a->connected()) {
			in_a->setType(incoming_type);
			in_b->setType(incoming_type);
			return true;
		}
		else if (in_a->var_type == incoming_type) {
			in_b->setType(incoming_type);
			return true;
		}
	}

	return false;
}

void NODES::BOOLEAN::Compare::onDisconnection(Port* port) {
	if (!in_a->connected() and !in_b->connected()) {
		in_a->setType(VAR_TYPE::NONE);
		in_b->setType(VAR_TYPE::NONE);
	}
}

void NODES::BOOLEAN::Compare::cascade(Port* port, const VAR_TYPE& var_type) {}

Variable NODES::BOOLEAN::Compare::getData(const Port* port) const {
	switch (enums->currentIndex()) {
	case 0: return Variable(in_a->getData() == in_b->getData());
	case 1: return Variable(in_a->getData() != in_b->getData());
	case 2: return Variable(in_a->getData()  > in_b->getData());
	case 3: return Variable(in_a->getData()  < in_b->getData());
	case 4: return Variable(in_a->getData() >= in_b->getData());
	case 5: return Variable(in_a->getData() <= in_b->getData());
	}
	return Variable(false);
}