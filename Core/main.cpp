#include "Window.hpp"

int main(int argc, char *argv[]) {
	QApplication* app = new QApplication(argc, argv);
	Window* window = new Window();
	window->showMaximized();
	return app->exec();
}