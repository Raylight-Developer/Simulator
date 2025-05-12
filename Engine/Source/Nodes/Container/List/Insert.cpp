#include "Nodes/Container/List/Insert.hpp"

NODES::CONTAINER::LIST::Insert::Insert() :
	Node(Node_Type::CONTAINER_LIST_INSERT, "Insert")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(120);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", Variable(0LL));
	di_value = DATA_I("Val", VAR_TYPE::NONE);

	eo_exec = EXEC_O("");
	do_list_pass = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	do_index_pass = DATA_O("", VAR_TYPE::INT);
	do_value_pass = DATA_O("", VAR_TYPE::NONE);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_value     ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
		do_value_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
		di_list      ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_list_pass ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
	});
}

void NODES::CONTAINER::LIST::Insert::exec(const Port* port) {
	auto list_data = di_list->getData();
	auto index_data = di_index->getData();
	auto value_data = di_value->getData();

	node_error = false;
	if (!(di_list->connected() && di_value->connected() && di_index->connected()) || list_data->empty()) {
		node_error = true;
		return;
	}
	const I64 list_index = *index_data->CAST(I64);
	list_data->listInsert(list_index, *value_data.get());
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