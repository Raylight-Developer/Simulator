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
	switch (var_type->currentIndex()) {
		case 1: {
			auto list_data = di_list->GET_LIST(F64);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 2: {
			auto list_data = di_list->GET_LIST(I64);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 3: {
			auto list_data = di_list->GET_LIST(bool);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 4: {
			auto list_data = di_list->GET_LIST(QString);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 5: {
			auto list_data = di_list->GET_LIST(F64_V2);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 6: {
			auto list_data = di_list->GET_LIST(F64_V3);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 7: {
			auto list_data = di_list->GET_LIST(F64_V4);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 8: {
			auto list_data = di_list->GET_LIST(Color);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 9: {
			auto list_data = di_list->GET_LIST(F64_Quat);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 10: {
			auto list_data = di_list->GET_LIST(F64_M2);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 11: {
			auto list_data = di_list->GET_LIST(F64_M3);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
		case 12: {
			auto list_data = di_list->GET_LIST(F64_M4);
			return make_shared<Variable>(to_I64(list_data->size()));
		}
	}
	return make_shared<Variable>(0LL);
}