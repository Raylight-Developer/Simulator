#include "Window.hpp"

int main(int argc, char *argv[]) {
	auto app = new GUI::Application(argc, argv);
	auto window = new Window();
	return app->exec();
}