#include "Window.hpp"
#include "Input.hpp"
#include "Session.hpp"

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
}

int main(int argc, char *argv[]) {
	qInstallMessageHandler(customMessageHandler);

	auto app = new GUI::Application(argc, argv);

	//auto style = QFile("./Resources/Style.css"); // https://bugreports.qt.io/browse/QTBUG-135340
	//style.open(QIODevice::ReadOnly | QIODevice::Text);
	//app->setStyleSheet(QTextStream(&style).readAll());

	QStringList fontFamilies = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont("./Resources/RobotoMono-Medium.ttf"));
	QFont font(fontFamilies.first());
	app->setFont(font);

	auto window = new Window();

	Input* input = new Input();
	app->installEventFilter(input);

	const int res = app->exec();

#ifdef NDEBUG
	window->session->file.saveFile("./Resources/Test-Release.sim");
#else
	window->session->file.saveFile("./Resources/Test-Debug.sim");
#endif

	LOGL(NL NL NL << SUCCESS("Shutdown") NL NL NL);

	return res;
}