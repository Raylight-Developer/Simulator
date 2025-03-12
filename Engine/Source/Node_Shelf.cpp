#include "Node_Shelf.hpp"

Node_Shelf::Node_Shelf(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::Direction::TopToBottom)
{
	tree = new NODE_SHELF::Tree(this);
	addWidget(tree);
}

NODE_SHELF::Tree::Tree(Node_Shelf* parent) :
	GUI::Tree(parent)
{
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);

	auto tree_math    = new GUI::Tree_Item(this, "Math");

	auto arithmetic   = new GUI::Tree_Item(tree_math, "Arithmetic"  , 1, { { 1000, "ARITHMETIC"   } });
	auto trigonometry = new GUI::Tree_Item(tree_math, "Trigonometry", 1, { { 1000, "TRIGONOMETRY" } });

	expandAll();
}

void NODE_SHELF::Tree::startDrag(Qt::DropActions actions) {
	if (QTreeWidgetItem* temp = currentItem()) {

		QMimeData* mimeData = new QMimeData;
		mimeData->setText("NODE");

		QByteArray type;
		QDataStream dataStreamType(&type, QIODevice::WriteOnly);
		dataStreamType << temp->data(0, 1000).toString();
		mimeData->setData("Type", type);

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}