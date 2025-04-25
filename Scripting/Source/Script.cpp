#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Test Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	PRINT(NL << "Loaded Test Script");
}

void Script::onUnload() {
	PRINT(NL << "Unloaded Test Script");
}

void Script::exec(const Exec_I* port) {
	execAllDownstream();
}

const Ptr_S<Variable> Script::getData(const Data_O* port) const {
	return nullptr;
}