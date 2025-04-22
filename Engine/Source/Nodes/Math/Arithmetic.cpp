#include "Nodes/Math/Arithmetic.hpp"

NODES::MATH::Arithmetic::Arithmetic() :
	Node(Node_Type::NONE, "Arithmetic")
{
	rect.setWidth(120);
	rect.setHeight(80);

	i_a = DATA_I("A", Variable(0.0));
	i_b = DATA_I("B", Variable(0.0));
	out = DATA_O("", VAR_TYPE::DOUBLE);

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "A+B", "A-B", "A*B", "A/B" });

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

Variable NODES::MATH::Arithmetic::getData(const Port* port) const {
	switch (enums->currentIndex()) {
		case 0: return Variable(i_a->GET_DATA(F64) + i_b->GET_DATA(F64));
		case 1: return Variable(i_a->GET_DATA(F64) - i_b->GET_DATA(F64));
		case 2: return Variable(i_a->GET_DATA(F64) * i_b->GET_DATA(F64));
		case 3: return Variable(i_a->GET_DATA(F64) / i_b->GET_DATA(F64));
	}
	return Variable(0.0);
}