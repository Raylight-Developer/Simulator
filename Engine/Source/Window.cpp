#include "Window.hpp"

#include "Session.hpp"

Window::Window() {
	setMouseTracking(true);

	session = new Session();
	session->window = this;
	Session::initialize(session);
	session->hook.pixel_ratio = devicePixelRatio();

	header = new Header(this);
	timeline = new Timeline(this);
	node_shelf = new Node_Shelf(this);
	node_editor = new Node_Editor(this);
	history_view = new History_View(this);
	variable_editor = new Variable_Editor(this);

	GUI::Splitter* splitter = new GUI::Splitter(this);
	splitter->addWidget(node_shelf);
	splitter->addWidget(node_editor);
	splitter->addWidget(variable_editor);

	viewport = new Viewport();

	GUI::Splitter* v_splitter = new GUI::Splitter(this, true);
	v_splitter->addWidget(timeline);
	v_splitter->addWidget(viewport);
	v_splitter->addWidget(splitter);
	v_splitter->setSizes({ 20, 1000, 1000 });

	GUI::Splitter* main_splitter = new GUI::Splitter(this);
	main_splitter->addWidget(v_splitter);
	main_splitter->addWidget(history_view);
	main_splitter->setSizes({ 2000, 400 });

	GUI::Linear_Contents* main_container = new GUI::Linear_Contents(this, QBoxLayout::Direction::TopToBottom);
	main_container->addWidget(header);
	main_container->addWidget(main_splitter);

	session->file.loadFile("./Resources/Test.sim");

	setCentralWidget(main_container);
	showMaximized();
	LOGL(<< SUCCESS << "Loaded Simulator v-" << SESSION->major_version << "." << SESSION->minor_version << "." << SESSION->patch_version);
}

Window::~Window() {
	delete session;
}