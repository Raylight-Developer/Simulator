#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

struct History_View : GUI::Linear_Contents {
	GUI::Tree* undo;
	GUI::Tree* redo;

	History_View(QWidget* parent);
	~History_View();
};