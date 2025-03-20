#pragma once

#include "KL.hpp"

#include "Scripting.hpp"
#include "Nodes.hpp"

class Node_Shelf;
namespace NODE_SHELF {
	class Tree;
}

class Node_Shelf : public GUI::Linear_Contents {
public:
	Node_Shelf(QWidget* parent = nullptr);

	NODE_SHELF::Tree* tree;
};

namespace NODE_SHELF {
	class Tree : public GUI::Tree {
	public:
		Tree(Node_Shelf* parent = nullptr);

		void startDrag(Qt::DropActions actions) override;
	};
}