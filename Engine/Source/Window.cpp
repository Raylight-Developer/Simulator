#include "Window.hpp"

#include "Session.hpp"

Window::Window() {
	Node_Shelf* shelf = new Node_Shelf(this);
	Node_Editor* node_editor = new Node_Editor(this);

	GUI::Splitter* splitter = new GUI::Splitter(this);
	splitter->addWidget(shelf);
	splitter->addWidget(node_editor);
	
	setCentralWidget(splitter);
	showMaximized();
}

Window::~Window() {
}