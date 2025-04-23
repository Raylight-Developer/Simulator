#include "Nodes/Hook/Input/Mouse.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse::Mouse() :
	Node(Node_Type::NONE, "Mouse")
{
	rect.setWidth(120);
	rect.setHeight(100);

	button = "Left";
	is_down = DATA_O("Is Down", VAR_TYPE::BOOL);

	buttons = new GUI::Options();
	buttons->setFixedSize(80, 20);
	buttons->addItems({ "Left", "Right", "Middle" });

	PROXY(buttons);
	proxy_buttons->setPos(30, 50);

	QObject::connect(buttons, &GUI::Options::currentTextChanged, [this](const QString& item) {
		button = "M " + item.toStdString();
	});
}

Variable NODES::HOOK::INPUT::Mouse::getData(const Port* port) const {
	return Variable(SESSION->hook.input_down[button]);
}