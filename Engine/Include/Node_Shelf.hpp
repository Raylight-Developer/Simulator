#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

#include "Scripting.hpp"
#include "Nodes.hpp"

struct Node_Shelf;
namespace NODE_SHELF {
	struct Tree;
}

struct Node_Shelf : GUI::Linear_Contents {
	Node_Shelf(QWidget* parent = nullptr);

	NODE_SHELF::Tree* tree;
};

namespace NODE_SHELF {
	struct Tree : GUI::Tree {
		GUI::Tree_Item* user_scripts;

		Tree(Node_Shelf* parent = nullptr);

		void startDrag(Qt::DropActions actions) override;
	};
}