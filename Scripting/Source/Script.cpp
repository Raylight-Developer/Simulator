#include "Script.hpp"

SCRIPT_INIT("Test Script")

void Script::onLoad() {
	PRINT(NL << "Loaded Test Script");
}

void Script::onUnload() {
	PRINT(NL << "Unloaded Test Script");
}

void Script::exec(const Port* port) {
	PRINT(NL << "Exec");
}

Variable Script::getData(const Port* port) const {
	return Variable();
}