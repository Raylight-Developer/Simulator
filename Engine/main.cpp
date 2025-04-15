#include "Window.hpp"
#include "Input.hpp"

int main(int argc, char *argv[]) {
	auto app = new GUI::Application(argc, argv);

	Input* input = new Input();
	app->installEventFilter(input);

	//auto style = QFile("./Resources/Style.css");
	//style.open(QIODevice::ReadOnly | QIODevice::Text);
	//app->setStyleSheet(QTextStream(&style).readAll());

	QStringList fontFamilies = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont("./Resources/RobotoMono-Medium.ttf"));
	QFont font(fontFamilies.first());
	app->setFont(font);

	auto window = new Window();
	return app->exec();
}