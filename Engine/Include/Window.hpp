#pragma once

#include "KL.hpp"

#include "Node_Editor.hpp"
#include "Node_Shelf.hpp"
#include "Viewport.hpp"

class Window : public GUI::Window {
public:
	Session* session;

	Window();
	~Window();
};