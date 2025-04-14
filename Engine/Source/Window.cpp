#include "Window.hpp"

#include "Session.hpp"

Window::Window() {
	session = new Session();
	Session::initialize(session);
	session->window = this;
	session->file = File::loadFile("./Resources/Default.sim");

	auto shelf = new Node_Shelf(this);
	auto timeline = new Timeline(this);
	auto node_editor = new Node_Editor(this);
	auto variable_editor = new Variable_Editor(this);

	auto viewport = new Viewport();
	auto container = QWidget::createWindowContainer(viewport, this);

	GUI::Splitter* splitter = new GUI::Splitter(this);
	splitter->addWidget(shelf);
	splitter->addWidget(node_editor);
	splitter->addWidget(variable_editor);

	GUI::Splitter* main_splitter = new GUI::Splitter(this, true);
	main_splitter->addWidget(timeline);
	main_splitter->addWidget(container);
	main_splitter->addWidget(splitter);
	main_splitter->setSizes({ 20, 1000, 1000 });
	
	setCentralWidget(main_splitter);
	showMaximized();
	LOGL(<< "Loaded Simulator v" << SESSION->major_version << "." << SESSION->minor_version << "." << SESSION->patch_version);
}

Window::~Window() {
	delete session;
}