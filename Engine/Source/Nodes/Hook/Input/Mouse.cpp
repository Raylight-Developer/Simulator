#include "Nodes/Hook/Input/Mouse.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Mouse::Mouse() :
	Node(Node_Type::HOOK_INPUT_MOUSE, "Mouse")
{
	rect.setWidth(100);
	rect.setHeight(80);

	button = "Left";
	do_is_down = DATA_O("Is Down", VAR_TYPE::BOOL);

	buttons = new GUI::Options();
	buttons->setFixedSize(80, 20);
	buttons->addItems({ "Left", "Right", "Middle" });

	PROXY(buttons);
	proxy_buttons->setPos(10, 50);

	QObject::connect(buttons, &GUI::Options::currentTextChanged, [this](const QString& item) {
		button = "M " + item.toStdString();
	});
}

Ptr_S<Variable> NODES::HOOK::INPUT::Mouse::getData(const Port* port) {
	return make_shared<Variable>(SIM_HOOK.input_down[button]);
}