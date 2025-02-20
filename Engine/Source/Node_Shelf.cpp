#include "Node_Shelf.hpp"

Node_Shelf::Node_Shelf(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::Direction::TopToBottom)
{
	tree = new NODE_SHELF::Tree(this);

	addWidget(tree);
}

NODE_SHELF::Tree::Tree(Node_Shelf* parent) :
	GUI::Tree(parent)
{}