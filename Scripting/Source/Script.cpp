#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Test Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	LOGL(<< "Loaded Test Script");
}

void Script::onUnload() {
	LOGL(<< "Unloaded Test Script");
}

void Script::exec(const Exec_I* port) {
	execAllDownstream();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return nullptr;
}