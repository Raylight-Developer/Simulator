#include "Nodes/Variables/Set.hpp"

#include "Session.hpp"

NODES::VARIABLE::Set::Set() :
	Node(Node_Type::VARIABLE_SET, "Set Var")
{
	rect.setWidth(120);
	rect.setHeight(80);

	ei_exec  = EXEC_I("");
	di_value = DATA_I("", VAR_TYPE::NONE);

	eo_exec       = EXEC_O("");
	do_value_pass = DATA_O("", VAR_TYPE::NONE);

	label = new GUI::Label();
	label->setFixedSize(80, 20);

	proxy_label = new GUI::Graphics_Widget(label, this);
	proxy_label->setPos(20, 30);
}

void NODES::VARIABLE::Set::exec(const Port* port) {
	node_error = false;
	if (!di_value->connected()) {
		node_error = true;
		return;
	}
	FILE.variables[var] = di_value->getData();
	eo_exec->exec();
}

Ptr_S<Variable> NODES::VARIABLE::Set::getData(const Port* port) {
	return FILE.variables[var];
}

void NODES::VARIABLE::Set::saveDetail(CORE::Lace& lace) const {
	lace NL << var;
}

void NODES::VARIABLE::Set::loadDetail(const Token_Array& tokens) {
	if (!tokens.empty()) {
		setVar(qstr(f_join(tokens[0])));
		FILE.variable_refs[var].push(shared_from_this());
	}
}

void NODES::VARIABLE::Set::h_setVar(const QString name) {
	H_PUSH(make_shared<Set_Variable>(static_pointer_cast<Set>(shared_from_this()), this->var, name));
}

void NODES::VARIABLE::Set::setVar(const QString name) {
	var = name;
	if (name != "") {
		const Variable* var_ref = FILE.variables[var].get();
		di_value->setType(var_ref->type, var_ref->container);
		do_value_pass->setType(var_ref->type, var_ref->container);
	}
	else {
		di_value->setType(VAR_TYPE::NONE, VAR_CONTAINER::NONE);
		do_value_pass->setType(VAR_TYPE::NONE, VAR_CONTAINER::NONE);
	}
	QFontMetrics metrics(label->font());
	const int textWidth = metrics.horizontalAdvance(var);
	const int width = ((textWidth + 19) / 20) * 20;
	rect.setWidth(40+width);
	delete proxy_label;
	label = new GUI::Label(nullptr, var);
	label->setFixedSize(width, 20);
	proxy_label = new GUI::Graphics_Widget(label, this);
	proxy_label->setPos(20, 30);
	eo_exec->rect.moveCenter(rect.topRight() + QPointF(0, eo_exec->rect.center().y()));
	do_value_pass->rect.moveCenter(rect.topRight() + QPointF(0, do_value_pass->rect.center().y()));
}

NODES::VARIABLE::Set::Set_Variable::Set_Variable(Ptr_S<Set> node, const QString& from, const QString& to) :
	CORE::CMD("Set Variable"),
	node(node),
	from(from),
	to(to)
{}

void NODES::VARIABLE::Set::Set_Variable::execute() const {
	node->setVar(to);
}

void NODES::VARIABLE::Set::Set_Variable::undo() {
	node->setVar(from);
}