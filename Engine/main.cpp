#include "Window.hpp"

int main(int argc, char *argv[]) {
	auto app = new GUI::Application(argc, argv);

	int font = QFontDatabase::addApplicationFont("./Resources/RobotoMono-Medium.ttf");
	if (font == -1) {
		cerr << "Failed to load Roboto Mono font!" << endl;
	}
	else {
		QStringList fontFamilies = QFontDatabase::applicationFontFamilies(font);
		if (!fontFamilies.empty()) {
			QFont font(fontFamilies.first());
			font.setPointSize(10);
			app->setFont(font);
		}
	}

	auto window = new Window();
	return app->exec();
}