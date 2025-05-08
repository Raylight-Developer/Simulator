#include "Nodes/Container/List/Access.hpp"

NODES::CONTAINER::LIST::Access::Access() :
	Node(Node_Type::CONTAINER_LIST_ACCESS, "Access")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(80);

	di_list  = DATA_I_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", VAR_TYPE::INT);

	do_value = DATA_O("", VAR_TYPE::NONE);
	do_index_pass = DATA_O("", VAR_TYPE::INT);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_list ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_value->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
	});
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Access::getData(const Port* port) {
	if (port == do_index_pass.get()) {
		return do_index_pass->getData();
	}
	node_error = false;
	if (!(di_list->connected() && di_index->connected() && do_value->connected())) {
		node_error = true;
		return nullptr;
	}
	const I64 list_index = *di_index->GET_DATA(I64);
	switch (var_type->currentIndex()) {
		case 1: {
			auto list_data = di_list->GET_LIST(F64);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 2: {
			auto list_data = di_list->GET_LIST(I64);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 3: {
			auto list_data = di_list->GET_LIST(bool);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 4: {
			auto list_data = di_list->GET_LIST(QString);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 5: {
			auto list_data = di_list->GET_LIST(F64_V2);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 6: {
			auto list_data = di_list->GET_LIST(F64_V3);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 7: {
			auto list_data = di_list->GET_LIST(F64_V4);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 8: {
			auto list_data = di_list->GET_LIST(Color);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 9: {
			auto list_data = di_list->GET_LIST(F64_Quat);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 10: {
			auto list_data = di_list->GET_LIST(F64_M2);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 11: {
			auto list_data = di_list->GET_LIST(F64_M3);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
		case 12: {
			auto list_data = di_list->GET_LIST(F64_M4);
			return make_shared<Variable>(list_data->cpy(list_index));
		}
	}
	return nullptr;
}

void NODES::CONTAINER::LIST::Access::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Access::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}