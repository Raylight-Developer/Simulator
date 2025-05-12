#include "Nodes/Container/List/Access.hpp"

NODES::CONTAINER::LIST::Access::Access() :
	Node(Node_Type::CONTAINER_LIST_ACCESS, "Access")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(120);
	rect.setHeight(80);

	di_list  = DATA_I_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_index = DATA_I("Index", Variable(0LL));

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
	auto list_data = di_list->getData();
	auto index_data = di_index->getData();

	auto error_var = make_shared<Variable>(static_cast<VAR_TYPE>(var_type->currentIndex()));

	node_error = false;
	if (!(di_list->connected() && di_index->connected()) || list_data->empty()) {
		node_error = true;
		return error_var;
	}

	const U64 list_index = to_U64(*index_data->CAST(I64));
	return make_shared<Variable>(list_data->listAtIndex(list_index));
}

void NODES::CONTAINER::LIST::Access::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Access::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}