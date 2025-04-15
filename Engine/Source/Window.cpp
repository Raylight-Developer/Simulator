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
	auto history_view = new History_View(this);
	auto variable_editor = new Variable_Editor(this);

	auto viewport = new Viewport();
	auto container = QWidget::createWindowContainer(viewport, this);

	GUI::Splitter* splitter = new GUI::Splitter(this);
	splitter->addWidget(shelf);
	splitter->addWidget(node_editor);
	splitter->addWidget(variable_editor);

	GUI::Splitter* v_splitter = new GUI::Splitter(this, true);
	v_splitter->addWidget(timeline);
	v_splitter->addWidget(container);
	v_splitter->addWidget(splitter);
	v_splitter->setSizes({ 20, 1000, 1000 });

	GUI::Splitter* main_splitter = new GUI::Splitter(this);

	main_splitter->addWidget(v_splitter);
	main_splitter->addWidget(history_view);
	main_splitter->setSizes({ 2000, 400 });
	
	setCentralWidget(main_splitter);
	showMaximized();
	LOGL(<< SUCCESS("Loaded Simulator v" << SESSION->major_version << "." << SESSION->minor_version << "." << SESSION->patch_version));
}

Window::~Window() {
	delete session;
}