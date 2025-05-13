#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Base Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	LOGL(<< "Loaded Base Script");
}

void Script::onUnload() {
	LOGL(<< "Unloaded Base Script");
}

void Script::exec(const Exec_I* port) {
	node_error = false; // To clear Highlight
	if (missingInputs()) {
		node_error = true; // Will Highlight Node
		return;
	}

	execAllDownstream();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	node_error = false; // To clear Highlight
	if (missingInputs()) {
		node_error = true; // Will Highlight Node
		return make_shared<Variable>();
	}

	return make_shared<Variable>();
}