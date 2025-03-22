#include "Script.hpp"

Script::Script() : SCRIPT("Test Script") {
	PRINT(NL << "Loaded Test Script");
}

Script::~Script() {
	PRINT(NL << "Unloaded Test Script");
}

void Script::onLoad() {
}

void Script::onUnload() {
}

void Script::exec(const Port* port) {
	PRINT(NL << "Exec");
}

Variable Script::getData(const Port* port) const {
	return Variable();
}