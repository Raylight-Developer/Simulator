#include "Nodes/Container/List/Push.hpp"

NODES::CONTAINER::LIST::Push::Push() :
	Node(Node_Type::CONTAINER_LIST_PUSH, "Push")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(100);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_value = DATA_I("Value", VAR_TYPE::NONE);

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

void NODES::CONTAINER::LIST::Push::exec(const Port* port) {
	auto list_data = di_list->getData();
	auto value_data = di_value->getData();

	node_error = false;
	if (!(di_list->connected() && di_value->connected()) || list_data->empty()) {
		node_error = true;
		return;
	}

	list_data->listPush(*value_data.get());
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Push::getData(const Port* port) {
	return di_list->getData();
}

void NODES::CONTAINER::LIST::Push::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Push::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}