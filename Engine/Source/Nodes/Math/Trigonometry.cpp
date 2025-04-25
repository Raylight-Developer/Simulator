#include "Nodes/Math/Trigonometry.hpp"

NODES::MATH::Trigonometry::Trigonometry() :
	Node(Node_Type::NONE, "Trigonometry")
{
	rect.setWidth(140);
	rect.setHeight(60);

	in = DATA_I("", VAR_TYPE::DOUBLE);
	out = DATA_O("", VAR_TYPE::DOUBLE);

	enums = new GUI::Options();
	enums->setFixedSize(100, 20);
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });

	PROXY(enums);
	proxy_enums->setPos(20, 30);
}

Variable NODES::MATH::Trigonometry::getData(const Port* port) const {
	const F64 x = in->GET_DATA(F64);
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