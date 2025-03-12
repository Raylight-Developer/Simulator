#include "Script.hpp"

Script::Script() : SCRIPT("Test Script") {
	cout << "Loaded Test Script" << endl;
}

void Script::exec(const Port* port) {
	cout << "Exec" << endl;
}

Variable Script::getData(const Port* port) const {
	return Variable();
}