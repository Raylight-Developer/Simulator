#include "Nodes/Container/List/Remove.hpp"

NODES::CONTAINER::LIST::Remove::Remove() :
	Node(Node_Type::NONE, "Remove")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	call = EXEC_I("");
	list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	index = DATA_I("Index", VAR_TYPE::INT);

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

void NODES::CONTAINER::LIST::Remove::exec(const Port* port) {
	const U64 list_index = to_U64(*index->GET_DATA(I64));
	switch (var_type->currentIndex()) {
		case 1: {
			list->GET_LIST(F64)->remove(list_index);
			break;
		}
		case 2: {
			list->GET_LIST(I64)->remove(list_index);
			break;
		}
		case 3: {
			list->GET_LIST(bool)->remove(list_index);
			break;
		}
		case 4: {
			list->GET_LIST(QString)->remove(list_index);
			break;
		}
		case 5: {
			list->GET_LIST(F64_V2)->remove(list_index);
			break;
		}
		case 6: {
			list->GET_LIST(F64_V3)->remove(list_index);
			break;
		}
		case 7: {
			list->GET_LIST(F64_V4)->remove(list_index);
			break;
		}
		case 8: {
			list->GET_LIST(Color)->remove(list_index);
			break;
		}
		case 9: {
			list->GET_LIST(F64_Quat)->remove(list_index);
			break;
		}
		case 10: {
			list->GET_LIST(F64_M2)->remove(list_index);
			break;
		}
		case 11: {
			list->GET_LIST(F64_M3)->remove(list_index);
			break;
		}
		case 12: {
			list->GET_LIST(F64_M4)->remove(list_index);
			break;
		}
	}
	call_pass->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Remove::getData(const Port* port) {
	return list->getData();
}