#include "Nodes/Container/List/Create.hpp"

#include "Session.hpp"

NODES::CONTAINER::LIST::Create::Create() :
	Node(Node_Type::CONTAINER_LIST_CREATE, "Create")
{
	header_color = QColor(25, 25, 75);
	rect.setWidth(140);
	rect.setHeight(120);

	ei_exec = EXEC_I("");
	di_list = DATA_I_C("List", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	di_size = DATA_I("Size", Variable(0LL));
	di_initial_value = DATA_I("Initial Val", VAR_TYPE::NONE);

	eo_exec = EXEC_O("");
	do_list_pass = DATA_O_C("", VAR_TYPE::NONE, VAR_CONTAINER::LIST);
	do_size_pass = DATA_O("", VAR_TYPE::INT);
	do_initial_value_pass = DATA_O("", VAR_TYPE::NONE);

	var_type = new GUI::Options();
	var_type->setFixedSize(100, 20);
	var_type->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});

	PROXY(var_type);
	proxy_var_type->setPos(10, 30);

	QObject::connect(var_type, &GUI::Options::currentIndexChanged, [this](int index) {
		di_list              ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		do_list_pass         ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::LIST);
		di_initial_value     ->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
		do_initial_value_pass->setType(static_cast<VAR_TYPE>(index), VAR_CONTAINER::NONE);
	});
}

void NODES::CONTAINER::LIST::Create::exec(const Port* port) { // TODO refactor all other nodes to match safety
	auto list_data = di_list->getData();
	auto size_data = di_size->getData();
	auto initial_value_data = di_initial_value->getData();

	node_error = false;
	if (!(di_list->connected() && di_size->connected()) || list_data->empty() || size_data->empty()) {
		node_error = true;
		return;
	}

	const I64 size = *size_data->CAST(I64);
	if (size > 65'536) {
		LOGL(<< ERROR("CONTAINER::LIST::CREATE Node Initializer size is larger than 2^16 (65'536)"));
		node_error = true;
		return;
	}

	list_data->listCreate(size, *initial_value_data.get());
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Create::getData(const Port* port) {
	if (port == do_list_pass.get()) {
		return di_list->getData();
	}
	else if (port == do_size_pass.get()) {
		return di_size->getData();
	}
	return di_initial_value->getData();
}

void NODES::CONTAINER::LIST::Create::saveDetail(CORE::Lace& lace) const {
	lace NL << var_type->currentText();
}

void NODES::CONTAINER::LIST::Create::loadDetail(const Token_Array& tokens) {
	var_type->setCurrentText(qstr(tokens[0][0]));
}