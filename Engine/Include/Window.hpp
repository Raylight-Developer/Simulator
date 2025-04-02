#pragma once

#include "KL.hpp"

#include "Variable_Editor.hpp"
#include "Node_Editor.hpp"
#include "Node_Shelf.hpp"
#include "Viewport.hpp"
#include "Timeline.hpp"

class Window : public GUI::Window {
public:
	Session* session;

	Window();
	~Window();
};