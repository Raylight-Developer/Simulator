#include "Variable_Editor.hpp"

#include "Session.hpp"

Variable_Editor::Variable_Editor(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::TopToBottom)
{
	auto add_var = new GUI::Button(this);
	add_var->setText("Add Variable");

	auto search = new GUI::Value_Input(this);

	auto list = new Varialbe_Editor::List(this);

	auto details = new GUI::Linear_Contents(this, QBoxLayout::Direction::TopToBottom);
	details->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	addWidget(add_var);
	addWidget(search);
	addWidget(list);
	addWidget(details);

	connect(add_var, &GUI::Button::pressed, [this, list]() {
		const QString var_name = QInputDialog::getText(nullptr, "Add Variable", "Enter Variable ID:");
		if (!var_name.isEmpty() and !FILE.variables.contains(var_name)) {
			FILE.variables[var_name] = Variable(VAR_TYPE::INT);
			list->addItem(var_name);
		}
	});

	connect(list, &GUI::List::currentItemChanged, [this, details](QListWidgetItem* item, QListWidgetItem* previous) {
		details->layout->clear();

		auto var_type_enums = new GUI::Options(this);
		var_type_enums->addItems({ "Integer", "Double", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});
		switch (FILE.variables[item->text()].type) {
			case VAR_TYPE::INT   : var_type_enums->setCurrentIndex( 0); break;
			case VAR_TYPE::DOUBLE: var_type_enums->setCurrentIndex( 1); break;
			case VAR_TYPE::BOOL  : var_type_enums->setCurrentIndex( 2); break;
			case VAR_TYPE::STRING: var_type_enums->setCurrentIndex( 3); break;
			case VAR_TYPE::VEC2  : var_type_enums->setCurrentIndex( 4); break;
			case VAR_TYPE::VEC3  : var_type_enums->setCurrentIndex( 5); break;
			case VAR_TYPE::VEC4  : var_type_enums->setCurrentIndex( 6); break;
			case VAR_TYPE::COLOR : var_type_enums->setCurrentIndex( 7); break;
			case VAR_TYPE::QUAT  : var_type_enums->setCurrentIndex( 8); break;
			case VAR_TYPE::MAT2  : var_type_enums->setCurrentIndex( 9); break;
			case VAR_TYPE::MAT3  : var_type_enums->setCurrentIndex(10); break;
			case VAR_TYPE::MAT4  : var_type_enums->setCurrentIndex(11); break;
		}

		auto var_container_enums = new GUI::Options(this);
		var_container_enums->addItems({ "Single", "Vector"});
		switch (FILE.variables[item->text()].container) {
			case VAR_CONTAINER::NONE  : var_container_enums->setCurrentIndex(0); break;
			case VAR_CONTAINER::VECTOR: var_container_enums->setCurrentIndex(1); break;
		}

		details->addWidget(new GUI::Linear_Contents(this, { new GUI::Label(this, "Type:"), var_type_enums }));
		details->addWidget(new GUI::Linear_Contents(this, { new GUI::Label(this, "Container:"), var_container_enums }));

		QObject::connect(var_container_enums, &GUI::Options::currentIndexChanged, [this, item](int index) {
			Variable var;
			const QString name = item->text();
			const auto type = FILE.variables[name].type;
			switch (index) {
				case 0: var = Variable(type, VAR_CONTAINER::NONE  ); break;
				case 1: var = Variable(type, VAR_CONTAINER::VECTOR); break;
			}
			updateVar(name, var);
		});

		QObject::connect(var_type_enums, &GUI::Options::currentIndexChanged, [this, item](int index) {
			Variable var;
			const QString name = item->text();
			const auto container = FILE.variables[name].container;
			switch (index) {
				case  0: var = Variable(VAR_TYPE::INT   , container); break;
				case  1: var = Variable(VAR_TYPE::DOUBLE, container); break;
				case  2: var = Variable(VAR_TYPE::BOOL  , container); break;
				case  3: var = Variable(VAR_TYPE::STRING, container); break;
				case  4: var = Variable(VAR_TYPE::VEC2  , container); break;
				case  5: var = Variable(VAR_TYPE::VEC3  , container); break;
				case  6: var = Variable(VAR_TYPE::VEC4  , container); break;
				case  7: var = Variable(VAR_TYPE::COLOR , container); break;
				case  8: var = Variable(VAR_TYPE::QUAT  , container); break;
				case  9: var = Variable(VAR_TYPE::MAT2  , container); break;
				case 10: var = Variable(VAR_TYPE::MAT3  , container); break;
				case 11: var = Variable(VAR_TYPE::MAT4  , container); break;
			}
			updateVar(name, var);
		});
	});
}

void Variable_Editor::updateVar(const QString& name, const Variable& var) const {
	FILE.variables[name] = var;
	for (Ptr_S<Node> node : FILE.variable_refs[name]) {
		if (node->node_type == NODES::Node_Type::VARIABLE_GET) {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Get>(node);
			if (node_def->out->connected()) {
				node_def->out->disconnect();
			}
			node_def->out->setType(var.type, var.container);
		}
		else if (node->node_type == NODES::Node_Type::VARIABLE_SET) {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Set>(node);
			if (node_def->in->connected()) {
				node_def->in->disconnect();
			}
			if (node_def->out->connected()) {
				node_def->out->disconnect();
			}
			node_def->in ->setType(var.type, var.container);
			node_def->out->setType(var.type, var.container);
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
		dataStreamType << "VARIABLE " + temp->text();
		mimeData->setData("Type", type);

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}