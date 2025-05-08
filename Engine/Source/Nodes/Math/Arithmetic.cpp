#include "Nodes/Math/Arithmetic.hpp"

NODES::MATH::Arithmetic::Arithmetic() :
	Node(Node_Type::MATH_ARITHMETIC, "Arithmetic")
{
	rect.setWidth(120);
	rect.setHeight(80);

	di_a = DATA_I("A", Variable(0.0));
	di_b = DATA_I("B", Variable(0.0));
	do_res = DATA_O("", VAR_TYPE::DOUBLE);

	enums = new GUI::Options();
	enums->setFixedSize(80, 20);
	enums->addItems({ "A+B", "A-B", "A*B", "A/B" });

	PROXY(enums);
	proxy_enums->setPos(30, 50);
}

Ptr_S<Variable> NODES::MATH::Arithmetic::getData(const Port* port) {
	switch (enums->currentIndex()) {
		case 0: return make_shared<Variable>(*di_a->GET_DATA(F64) + *di_b->GET_DATA(F64));
		case 1: return make_shared<Variable>(*di_a->GET_DATA(F64) - *di_b->GET_DATA(F64));
		case 2: return make_shared<Variable>(*di_a->GET_DATA(F64) * *di_b->GET_DATA(F64));
		case 3: return make_shared<Variable>(*di_a->GET_DATA(F64) / *di_b->GET_DATA(F64));
	}
	return nullptr;
}

void NODES::MATH::Arithmetic::saveDetail(CORE::Lace& lace) const {
	lace NL << enums->currentText();
}

void NODES::MATH::Arithmetic::loadDetail(const Token_Array& tokens) {
	enums->setCurrentText(qstr(tokens[0][0]));
}