#include "Window.hpp"

#include "Session.hpp"

Window::Window() {
	node_editor = new Node_Editor(this);
	setCentralWidget(node_editor);
	showMaximized();
}

Window::~Window() {
}