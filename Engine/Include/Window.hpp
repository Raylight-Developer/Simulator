#pragma once

#include "Include.hpp"
#include "QT.hpp"

#include "Node_Editor.hpp"

class Window : public GUI::Window {
public:
	Node_Editor* node_editor;

	Window();
	~Window();
};