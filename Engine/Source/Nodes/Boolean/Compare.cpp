#include "Nodes/Boolean/Compare.hpp"

NODES::BOOLEAN::Compare::Compare() :
	Node(Node_Type::NONE, "Compare")
{
	rect.setWidth(120);
	rect.setHeight(80);

	in_a = DATA_I("", VAR_TYPE::NONE);
	in_b = DATA_I("", VAR_TYPE::NONE);
	out  = DATA_O("", VAR_TYPE::BOOL);

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "==", "!=", ">", "<", ">=", "<=", "Sign"});

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

Ptr_S<Variable> NODES::BOOLEAN::Compare::getData(const Port* port) {
	//switch (enums->currentIndex()) {
	//	case 0: return Variable(in_a->getData() == in_b->getData());
	//	case 1: return Variable(in_a->getData() != in_b->getData());
	//	case 2: return Variable(in_a->getData()  > in_b->getData());
	//	case 3: return Variable(in_a->getData()  < in_b->getData());
	//	case 4: return Variable(in_a->getData() >= in_b->getData());
	//	case 5: return Variable(in_a->getData() <= in_b->getData());
	//}
	return make_shared<Variable>(false);
}