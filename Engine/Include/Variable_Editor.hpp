#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

#include "Node.hpp"

struct Variable_Editor;
namespace Varialbe_Editor {
	struct List;
}

struct Variable_Editor : GUI::Linear_Contents {
	Varialbe_Editor::List* list;

	Variable_Editor(QWidget* parent);

	void updateVar(const QString& name, const Variable& var) const;
};

namespace Varialbe_Editor {
	struct List : GUI::List {
		List(Variable_Editor* parent = nullptr);

		void startDrag(Qt::DropActions actions) override;
	};
}