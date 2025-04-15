#include "Nodes/Variables/Set.hpp"

#include "Session.hpp"

NODES::VARIABLES::Set::Set() :
	Node("Set Var")
{
	rect.setWidth(120);
	rect.setHeight(80);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");
	in  = DATA_I("", VAR_TYPE::NONE);
	out = DATA_O("", VAR_TYPE::NONE);

	label = new GUI::Label();
	label->setFixedSize(80, 20);

	PROXY(label);
	proxy_label->setPos(20, 30);
}

void NODES::VARIABLES::Set::h_setVar(const QString name) {
	H_PUSH(make_shared<Set_Variable>(this, this->var, name));
}

void NODES::VARIABLES::Set::setVar(const QString name) {
	var = name;
	out->setType(SESSION->variables[var].type);
	label->setText(var);
}

void NODES::VARIABLES::Set::exec(const Port* port) {
	if (in->connected()) {
		SESSION->variables[var] = in->getData();
	}
	exec_out->exec();
}

Variable NODES::VARIABLES::Set::getData(const Port* port) const {
	return SESSION->variables[var];
}

NODES::VARIABLES::Set::Set_Variable::Set_Variable(Set* node, const QString& from, const QString& to):
	CORE::CMD("Set Variable"),
	node(node),
	from(from),
	to(to)
{}

void NODES::VARIABLES::Set::Set_Variable::execute() const {
	node->setVar(to);
}

void NODES::VARIABLES::Set::Set_Variable::undo() {
	node->setVar(from);
}