#include "Nodes/Container/List/Clear.hpp"

NODES::CONTAINER::LIST::Clear::Clear() :
	Node(Node_Type::CONTAINER_LIST_CLEAR, "Clear")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(80);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

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

void NODES::CONTAINER::LIST::Clear::exec(const Port* port) {
	auto list_data = di_list->getData();

	node_error = false;
	if (!di_list->connected() || list_data->empty()) {
		node_error = true;
		return;
	}

	list_data->listClear();
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Clear::getData(const Port* port) {
	return di_list->getData();
}

void NODES::CONTAINER::LIST::Clear::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Clear::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}