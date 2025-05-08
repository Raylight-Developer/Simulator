#include "Nodes/Container/List/Modify.hpp"

NODES::CONTAINER::LIST::Modify::Modify() :
	Node(Node_Type::CONTAINER_LIST_MODIFY, "Modify")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(120);

	ei_exec  = EXEC_I("");
	di_list  = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", VAR_TYPE::INT);
	di_value = DATA_I("Value", VAR_TYPE::NONE);

	eo_exec  = EXEC_O("");
	do_list_pass  = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	do_index_pass = DATA_O("", VAR_TYPE::INT);
	do_value_pass = DATA_O("", VAR_TYPE::NONE);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_list ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		di_value->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
		do_list_pass ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_value_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
	});
}

void NODES::CONTAINER::LIST::Modify::exec(const Port* port) {
	node_error = false;
	if (!(di_list->connected() && di_value->connected() && di_index->connected())) {
		eo_exec->exec();
		node_error = true;
		return;
	}
	const I64 list_index = *di_index->GET_DATA(I64);
	switch (var_type->currentIndex()) {
		case 1: {
			di_list->GET_LIST(F64)->set(list_index, *di_value->GET_DATA(F64));
			break;
		}
		case 2: {
			di_list->GET_LIST(I64)->set(list_index, *di_value->GET_DATA(I64));
			break;
		}
		case 3: {
			di_list->GET_LIST(bool)->set(list_index, *di_value->GET_DATA(bool));
			break;
		}
		case 4: {
			di_list->GET_LIST(QString)->set(list_index, *di_value->GET_DATA(QString));
			break;
		}
		case 5: {
			auto list = di_list->GET_LIST(F64_V2);
			list->set(list_index, *di_value->GET_DATA(F64_V2));
			break;
		}
		case 6: {
			di_list->GET_LIST(F64_V3)->set(list_index, *di_value->GET_DATA(F64_V3));
			break;
		}
		case 7: {
			di_list->GET_LIST(F64_V4)->set(list_index, *di_value->GET_DATA(F64_V4));
			break;
		}
		case 8: {
			di_list->GET_LIST(Color)->set(list_index, *di_value->GET_DATA(Color));
			break;
		}
		case 9: {
			di_list->GET_LIST(F64_Quat)->set(list_index, *di_value->GET_DATA(F64_Quat));
			break;
		}
		case 10: {
			di_list->GET_LIST(F64_M2)->set(list_index, *di_value->GET_DATA(F64_M2));
			break;
		}
		case 11: {
			di_list->GET_LIST(F64_M3)->set(list_index, *di_value->GET_DATA(F64_M3));
			break;
		}
		case 12: {
			di_list->GET_LIST(F64_M4)->set(list_index, *di_value->GET_DATA(F64_M4));
			break;
		}
	}
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Modify::getData(const Port* port) {
	if (port == do_list_pass.get()) {
		di_list->getData();
	}
	else if (port == do_index_pass.get()) {
		return di_index->getData();
	}
	else if (port == do_value_pass.get()) {
		return di_value->getData();
	}
	return nullptr;
}

void NODES::CONTAINER::LIST::Modify::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Modify::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}