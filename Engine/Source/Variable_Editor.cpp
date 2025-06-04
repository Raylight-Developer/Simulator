#include "Variable_Editor.hpp"

#include "Session.hpp"

Variable_Editor::Variable_Editor(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::TopToBottom)
{
	auto add_var = new GUI::Button(this);
	add_var->setText("Add Variable");

	auto search = new GUI::Value_Input(this);

	list = new Varialbe_Editor::List(this);

	auto details = new GUI::Linear_Contents(this, QBoxLayout::Direction::TopToBottom);
	details->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	addWidget(add_var);
	addWidget(search);
	addWidget(list);
	addWidget(details);

	connect(add_var, &GUI::Button::pressed, [this]() {
		const QString var_name = QInputDialog::getText(nullptr, "Add Variable", "Enter Variable ID:");
		if (!var_name.isEmpty() && !FILE.variables.contains(var_name)) {
			FILE.variables[var_name] = make_shared<Variable>(VAR_TYPE::NONE);
			list->addItem(var_name);
		}
	});

	connect(list, &GUI::List::currentItemChanged, [this, details](QListWidgetItem* item, QListWidgetItem* previous) {
		details->layout->clear();

		auto var_type_enums = new GUI::Options(this);
		var_type_enums->addItems({ "", "Double", "Integer", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});
		var_type_enums->setCurrentIndex(static_cast<I32>(FILE.variables[item->text()]->type) - 2);

		auto var_container_enums = new GUI::Options(this);
		var_container_enums->addItems({ "Single", "List"});
		switch (FILE.variables[item->text()]->container) {
			case VAR_CONTAINER::NONE: var_container_enums->setCurrentIndex(0); break;
			case VAR_CONTAINER::LIST: var_container_enums->setCurrentIndex(1); break;
		}

		details->addWidget(new GUI::Linear_Contents(this, { new GUI::Label(this, "Type:"), var_type_enums }));
		details->addWidget(new GUI::Linear_Contents(this, { new GUI::Label(this, "Container:"), var_container_enums }));

		QObject::connect(var_container_enums, &GUI::Options::currentIndexChanged, [this, item](int index) {
			Variable var;
			const QString name = item->text();
			const auto type = FILE.variables[name]->type;
			switch (index) {
				case 0: var = Variable(type, VAR_CONTAINER::NONE); break;
				case 1: var = Variable(type, VAR_CONTAINER::LIST); break;
			}
			updateVar(name, var);
		});

		QObject::connect(var_type_enums, &GUI::Options::currentIndexChanged, [this, item](int index) {
			const QString name = item->text();
			const auto container = FILE.variables[name]->container;
			Variable var = Variable(static_cast<VAR_TYPE>(index), container);
			updateVar(name, var);
		});

		// TODO delete variable
		// TODO rename variable
	});
}

void Variable_Editor::updateVar(const QString& name, const Variable& var) const {
	FILE.variables[name] = make_shared<Variable>(var);
	for (Ptr_S<Node> node : FILE.variable_refs[name]) {
		if (node->node_type == NODES::Node_Type::VARIABLE_GET) {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Get>(node);
			if (node_def->do_var->connected()) {
				node_def->do_var->disconnect();
			}
			node_def->do_var->setType(var.type, var.container);
		}
		else if (node->node_type == NODES::Node_Type::VARIABLE_SET) {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Set>(node);
			if (node_def->di_value->connected()) {
				node_def->di_value->disconnect();
			}
			if (node_def->do_value_pass->connected()) {
				node_def->do_value_pass->disconnect();
			}
			node_def->di_value->setType(var.type, var.container);
			node_def->do_value_pass->setType(var.type, var.container);
		}
	}
}

Varialbe_Editor::List::List(Variable_Editor* parent) :
	GUI::List(parent)
{
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);
}

void Varialbe_Editor::List::startDrag(Qt::DropActions actions) {
	if (QListWidgetItem* temp = currentItem()) {

		QMimeData* mimeData = new QMimeData;
		mimeData->setText("NODE");

		QByteArray type;
		QDataStream dataStreamType(&type, QIODevice::WriteOnly);
		dataStreamType << QStringLiteral("VARIABLE ") + temp->text();
		mimeData->setData("Type", type);

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}