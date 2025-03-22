#include "Window.hpp"

#include "Session.hpp"

Window::Window() {
	Node_Shelf* shelf = new Node_Shelf(this);
	Node_Editor* node_editor = new Node_Editor(this);

	Viewport* viewport = new Viewport();
	QWidget* container = QWidget::createWindowContainer(viewport, this);

	GUI::Splitter* splitter = new GUI::Splitter(this);
	splitter->addWidget(shelf);
	splitter->addWidget(node_editor);

	GUI::Splitter* main_splitter = new GUI::Splitter(this, true);
	main_splitter->addWidget(container);
	main_splitter->addWidget(splitter);
	main_splitter->setSizes({ 1000, 500 });
	
	setCentralWidget(main_splitter);
	showMaximized();
	PRINT(NL << "Loaded");
}

Window::~Window() {
}