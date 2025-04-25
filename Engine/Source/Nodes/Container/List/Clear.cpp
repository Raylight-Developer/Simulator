#include "Nodes/Container/List/Clear.hpp"

NODES::CONTAINER::LIST::Clear::Clear() :
	Node(Node_Type::NONE, "Clear")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	call = EXEC_I("");
	list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

	call_pass = EXEC_O("");
	list_pass = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		list     ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		list_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
	});
}

void NODES::CONTAINER::LIST::Clear::exec(const Port* port) {
	switch (var_type->currentIndex()) {
		case 1: {
			list->GET_LIST(F64)->clear();
			break;
		}
		case 2: {
			list->GET_LIST(I64)->clear();
			break;
		}
		case 3: {
			list->GET_LIST(bool)->clear();
			break;
		}
		case 4: {
			list->GET_LIST(QString)->clear();
			break;
		}
		case 5: {
			list->GET_LIST(F64_V2)->clear();
			break;
		}
		case 6: {
			list->GET_LIST(F64_V3)->clear();
			break;
		}
		case 7: {
			list->GET_LIST(F64_V4)->clear();
			break;
		}
		case 8: {
			list->GET_LIST(Color)->clear();
			break;
		}
		case 9: {
			list->GET_LIST(F64_Quat)->clear();
			break;
		}
		case 10: {
			list->GET_LIST(F64_M2)->clear();
			break;
		}
		case 11: {
			list->GET_LIST(F64_M3)->clear();
			break;
		}
		case 12: {
			list->GET_LIST(F64_M4)->clear();
			break;
		}
	}
	call_pass->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Clear::getData(const Port* port) {
	return list->getData();
}