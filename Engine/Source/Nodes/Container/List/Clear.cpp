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
	node_error = false;
	if (!di_list->connected()) {
		eo_exec->exec();
		node_error = true;
		return;
	}
	switch (var_type->currentIndex()) {
		case 1: {
			di_list->GET_LIST(F64)->clear();
			break;
		}
		case 2: {
			di_list->GET_LIST(I64)->clear();
			break;
		}
		case 3: {
			di_list->GET_LIST(bool)->clear();
			break;
		}
		case 4: {
			di_list->GET_LIST(QString)->clear();
			break;
		}
		case 5: {
			di_list->GET_LIST(F64_V2)->clear();
			break;
		}
		case 6: {
			di_list->GET_LIST(F64_V3)->clear();
			break;
		}
		case 7: {
			di_list->GET_LIST(F64_V4)->clear();
			break;
		}
		case 8: {
			di_list->GET_LIST(Color)->clear();
			break;
		}
		case 9: {
			di_list->GET_LIST(F64_Quat)->clear();
			break;
		}
		case 10: {
			di_list->GET_LIST(F64_M2)->clear();
			break;
		}
		case 11: {
			di_list->GET_LIST(F64_M3)->clear();
			break;
		}
		case 12: {
			di_list->GET_LIST(F64_M4)->clear();
			break;
		}
	}
	eo_exec->exec();
}

Ptr_S<Variable> NODES::CONTAINER::LIST::Clear::getData(const Port* port) {
	return di_list->getData();
}