#include "Nodes/Container/List/Remove.hpp"

NODES::CONTAINER::LIST::Remove::Remove() :
	Node(Node_Type::CONTAINER_LIST_REMOVE, "Remove")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", VAR_TYPE::INT);

	eo_exec = EXEC_O("");
	do_list_pass = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_list     ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_list_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
	});
}

void NODES::CONTAINER::LIST::Remove::exec(const Port* port) {
	auto list_data = di_list->getData();
	auto index_data = di_index->getData();

	node_error = false;
	if (!(di_list->connected()) || list_data->empty()) {
		node_error = true;
		return;
	}

	const U64 list_index = to_U64(*di_index->GET_DATA(I64));
	list_data->listRemove(list_index);
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Remove::getData(const Port* port) {
	return di_list->getData();
}

void NODES::CONTAINER::LIST::Remove::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Remove::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}