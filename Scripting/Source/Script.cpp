#include "Script.hpp"

Script::Script() : SCRIPT("Test Script") {
	LOG NL << "Loaded Test Script"; FLUSH;
}

Script::~Script() {
	LOG NL << "Unloaded Test Script"; FLUSH;
}

void Script::onLoad() {
}

void Script::onUnload() {
}

void Script::exec(const Port* port) {
	LOG NL << "Exec"; FLUSH;
}

Variable Script::getData(const Port* port) const {
	return Variable();
}