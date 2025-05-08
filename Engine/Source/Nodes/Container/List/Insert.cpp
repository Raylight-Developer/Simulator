#include "Nodes/Container/List/Insert.hpp"

NODES::CONTAINER::LIST::Insert::Insert() :
	Node(Node_Type::CONTAINER_LIST_INSERT, "Insert")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(120);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", VAR_TYPE::INT);
	di_value = DATA_I("Val", VAR_TYPE::NONE);

	eo_exec = EXEC_O("");
	do_list_pass = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_value    ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
		di_list     ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_list_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
	});
}

void NODES::CONTAINER::LIST::Insert::exec(const Port* port) {
	node_error = false;
	if (!(di_list->connected() && di_value->connected() && di_index->connected())) {
		eo_exec->exec();
		node_error = true;
		return;
	}
	const U64 list_index = to_U64(*di_index->GET_DATA(I64));
	switch (var_type->currentIndex()) {
		case 1: {
			di_list->GET_LIST(F64)->insert(list_index, *di_value->GET_DATA(F64));
			break;
		}
		case 2: {
			di_list->GET_LIST(I64)->insert(list_index, *di_value->GET_DATA(I64));
			break;
		}
		case 3: {
			di_list->GET_LIST(bool)->insert(list_index, *di_value->GET_DATA(bool));
			break;
		}
		case 4: {
			di_list->GET_LIST(QString)->insert(list_index, *di_value->GET_DATA(QString));
			break;
		}
		case 5: {
			di_list->GET_LIST(F64_V2)->insert(list_index, *di_value->GET_DATA(F64_V2));
			break;
		}
		case 6: {
			di_list->GET_LIST(F64_V3)->insert(list_index, *di_value->GET_DATA(F64_V3));
			break;
		}
		case 7: {
			di_list->GET_LIST(F64_V4)->insert(list_index, *di_value->GET_DATA(F64_V4));
			break;
		}
		case 8: {
			di_list->GET_LIST(Color)->insert(list_index, *di_value->GET_DATA(Color));
			break;
		}
		case 9: {
			di_list->GET_LIST(F64_Quat)->insert(list_index, *di_value->GET_DATA(F64_Quat));
			break;
		}
		case 10: {
			di_list->GET_LIST(F64_M2)->insert(list_index, *di_value->GET_DATA(F64_M2));
			break;
		}
		case 11: {
			di_list->GET_LIST(F64_M3)->insert(list_index, *di_value->GET_DATA(F64_M3));
			break;
		}
		case 12: {
			di_list->GET_LIST(F64_M4)->insert(list_index, *di_value->GET_DATA(F64_M4));
			break;
		}
	}
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Insert::getData(const Port* port) {
	return di_list->getData();
}

void NODES::CONTAINER::LIST::Insert::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Insert::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}