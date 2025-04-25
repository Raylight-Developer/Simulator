#include "Nodes/Variables/Get.hpp"

#include "Session.hpp"

NODES::VARIABLE::Get::Get() :
	Node(Node_Type::VARIABLE_GET, "Get Var")
{
	rect.setWidth(120);
	rect.setHeight(60);

	out = DATA_O("", VAR_TYPE::BLOCKED);

	label = new GUI::Label();
	label->setFixedSize(80, 20);

	PROXY(label);
	proxy_label->setPos(20, 30);
}

void NODES::VARIABLE::Get::setVar(const QString name) {
	var = name;
	out->setType(FILE.variables[var].type, FILE.variables[var].container);
	label->setText(var);
}

Variable NODES::VARIABLE::Get::getData(const Port* port) const {
	return FILE.variables[var];
}