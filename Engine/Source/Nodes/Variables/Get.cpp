#include "Nodes/Variables/Get.hpp"

#include "Session.hpp"

NODES::VARIABLE::Get::Get() :
	Node(Node_Type::VARIABLE_GET, "Get Var")
{
	rect.setWidth(120);
	rect.setHeight(60);

	do_var = DATA_O("", VAR_TYPE::NONE);

	label = new GUI::Label();
	label->setFixedSize(80, 20);

	PROXY(label);
	proxy_label->setPos(20, 30);
}

Ptr_S<Variable> NODES::VARIABLE::Get::getData(const Port* port) {
	return FILE.variables[var];
}

void NODES::VARIABLE::Get::saveDetail(CORE::Lace& lace) const {
	lace NL << var;
}

void NODES::VARIABLE::Get::loadDetail(const Token_Array& tokens) {
	if (!tokens.empty()) {
		setVar(qstr(f_join(tokens[0])));
		FILE.variable_refs[var].push(shared_from_this());
	}
}

void NODES::VARIABLE::Get::h_setVar(const QString name) {
	H_PUSH(make_shared<Set_Variable>(static_pointer_cast<Get>(shared_from_this()), this->var, name));
}

void NODES::VARIABLE::Get::setVar(const QString name) {
	var = name;
	do_var->setType(FILE.variables[var]->type, FILE.variables[var]->container);
	label->setText(var);
}

NODES::VARIABLE::Get::Set_Variable::Set_Variable(Ptr_S<Get> node, const QString& from, const QString& to):
	CORE::CMD("Set Variable"),
	node(node),
	from(from),
	to(to)
{}

void NODES::VARIABLE::Get::Set_Variable::execute() const {
	node->setVar(to);
}

void NODES::VARIABLE::Get::Set_Variable::undo() {
	node->setVar(from);
}