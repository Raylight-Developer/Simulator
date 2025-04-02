#pragma once

#include "KL.hpp"

struct Variable_Editor;
namespace Varialbe_Editor {
	struct List;
}

struct Variable_Editor : GUI::Linear_Contents {
	Variable_Editor(QWidget* parent);
};

namespace Varialbe_Editor {
	struct List : GUI::List {
		List(Variable_Editor* parent = nullptr);

		void startDrag(Qt::DropActions actions) override;
	};
}