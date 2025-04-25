#include "Nodes/Hook/Input/Key.hpp"

#include "Session.hpp"

NODES::HOOK::INPUT::Key::Key() :
	Node(Node_Type::NONE, "Key")
{
	rect.setWidth(100);
	rect.setHeight(80);

	key = "A";
	is_down = DATA_O("Is Down", VAR_TYPE::BOOL);

	keys = new GUI::Options();
	keys->setFixedSize(80, 20);
	keys->addItems({
		"A", "B", "C", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="
		"~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+"
		".", "<", "/", ";", "'", "[", "]", "\\",
		"<", ">", "?", ":", "\"", "{", "}", "|",
		"Alt", "Ctrl", "Shift", "Tab", "Space", "Enter", "Backspace", "Delete"
	});

	PROXY(keys);
	proxy_keys->setPos(10, 50);

	QObject::connect(keys, &GUI::Options::currentTextChanged, [this](const QString& item) {
		key = item.toStdString();
	});
}

Ptr_S<Variable> NODES::HOOK::INPUT::Key::getData(const Port* port) {
	return make_shared<Variable>(SESSION->hook.input_down[key]);
}