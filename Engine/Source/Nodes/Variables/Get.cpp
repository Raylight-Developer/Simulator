#include "Nodes/Variables/Get.hpp"

#include "Session.hpp"

NODES::VARIABLES::Get::Get() :
	Node("VARIABLES::GET", "Get Var")
{
	rect.setWidth(120);
	rect.setHeight(60);

	out = DATA_O("", VAR_TYPE::BLOCKED);

	label = new GUI::Label();
	label->setFixedSize(80, 20);

	PROXY(label);
	proxy_label->setPos(20, 30);
}

void NODES::VARIABLES::Get::setVar(const QString name) {
	var = name;
	out->setType(SESSION->variables[var].type);
	label->setText(var);
}

Variable NODES::VARIABLES::Get::getData(const Port* port) const {
	return SESSION->variables[var];
}