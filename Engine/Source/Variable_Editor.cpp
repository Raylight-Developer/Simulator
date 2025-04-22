#include "Variable_Editor.hpp"

#include "Session.hpp"

Variable_Editor::Variable_Editor(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::TopToBottom)
{
	auto add_var = new GUI::Button(this);
	add_var->setText("Add Variable");

	auto search = new GUI::Value_Input(this);

	auto list = new Varialbe_Editor::List(this);

	auto details = new GUI::Linear_Contents(this);

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

		auto enums = new GUI::Options(this);
		enums->addItems({ "Integer", "Double", "Bool", "String", "Vec2", "Vec3", "Vec4", "Color", "Quat", "Mat2", "Mat3", "Mat4"});
		switch (FILE.variables[item->text()].type) {
			case VAR_TYPE::INT   : enums->setCurrentIndex( 0); break;
			case VAR_TYPE::DOUBLE: enums->setCurrentIndex( 1); break;
			case VAR_TYPE::BOOL  : enums->setCurrentIndex( 2); break;
			case VAR_TYPE::STRING: enums->setCurrentIndex( 3); break;
			case VAR_TYPE::VEC2  : enums->setCurrentIndex( 4); break;
			case VAR_TYPE::VEC3  : enums->setCurrentIndex( 5); break;
			case VAR_TYPE::VEC4  : enums->setCurrentIndex( 6); break;
			case VAR_TYPE::COLOR : enums->setCurrentIndex( 7); break;
			case VAR_TYPE::QUAT  : enums->setCurrentIndex( 8); break;
			case VAR_TYPE::MAT2  : enums->setCurrentIndex( 9); break;
			case VAR_TYPE::MAT3  : enums->setCurrentIndex(10); break;
			case VAR_TYPE::MAT4  : enums->setCurrentIndex(11); break;
		}

		details->addWidget(new GUI::Linear_Contents(this, { new GUI::Label(this, "Var Type:"), enums }));

		QObject::connect(enums, &GUI::Options::currentIndexChanged, [this, item](int index) {
			Variable var;
			switch (index) {
				case  0: var = Variable(VAR_TYPE::INT   ); break;
				case  1: var = Variable(VAR_TYPE::DOUBLE); break;
				case  2: var = Variable(VAR_TYPE::BOOL  ); break;
				case  3: var = Variable(VAR_TYPE::STRING); break;
				case  4: var = Variable(VAR_TYPE::VEC2  ); break;
				case  5: var = Variable(VAR_TYPE::VEC3  ); break;
				case  6: var = Variable(VAR_TYPE::VEC4  ); break;
				case  7: var = Variable(VAR_TYPE::COLOR ); break;
				case  8: var = Variable(VAR_TYPE::QUAT  ); break;
				case  9: var = Variable(VAR_TYPE::MAT2  ); break;
				case 10: var = Variable(VAR_TYPE::MAT3  ); break;
				case 11: var = Variable(VAR_TYPE::MAT4  ); break;
			}
			FILE.variables[item->text()] = var;
			for (Ptr_S<Node> node : FILE.variable_refs[item->text()]) {
				if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Get>(node)) {
					if (node_def->out->connected()) {
						node_def->out->disconnect();
					}
					node_def->out->setType(var.type);
				}
				else if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Set>(node)) {
					if (node_def->in->connected()) {
						node_def->in->disconnect();
					}
					if (node_def->out->connected()) {
						node_def->out->disconnect();
					}
					node_def->in->setType(var.type);
					node_def->out->setType(var.type);
				}
			}
		});
	});
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