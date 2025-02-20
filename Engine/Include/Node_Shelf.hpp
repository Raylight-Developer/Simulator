#pragma once

#include "Include.hpp"
#include "QT.hpp"

#include "Scripting.hpp"

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
	};
}