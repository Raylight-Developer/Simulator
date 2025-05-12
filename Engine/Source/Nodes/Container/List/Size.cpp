#include "Nodes/Container/List/Size.hpp"

NODES::CONTAINER::LIST::Size::Size() :
	Node(Node_Type::CONTAINER_LIST_SIZE, "Size")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(60);

	di_list = DATA_I_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);

	do_size = DATA_O("", VAR_TYPE::INT);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_list->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
	});
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Size::getData(const Port* port) {
	auto list_data = di_list->getData();

	node_error = false;
	if (!di_list->connected() || list_data->empty()) {
		node_error = true;
		return make_shared<Variable>(0LL);
	}

	return make_shared<Variable>(to_I64(list_data->listSize()));
}

void NODES::CONTAINER::LIST::Size::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Size::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}