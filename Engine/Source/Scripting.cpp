#include "Scripting.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

NODES::SCRIPT::Script::Script(const QString& id, Session* session) :
	Node(Node_Type::SCRIPT, id),
	session(session),
	path("")
{
	header_color = QColor(25, 75, 25);
}

NODES::SCRIPT::Script::~Script() {
}

void NODES::SCRIPT::loadDLL(HINSTANCE& dynlib, const QString& dll_path) {
	const string dll_str = dll_path.toStdString();
	wstring stemp = wstring(dll_str.begin(), dll_str.end());
	LPCWSTR file_path = stemp.c_str();
	//LOG NL << "[DLL Loading] Loading: " << dll_str; FLUSH;
	dynlib = LoadLibrary(file_path);
	if (!dynlib) {
		const unsigned int errorCode = static_cast<unsigned int>(GetLastError());
		LOG NL <<"[DLL Loading] LoadLibrary " << ERROR << "Failed" << " with error code : " << errorCode; FLUSH;
		exit(EXIT_FAILURE);
	}
	//LOG NL << "[DLL Loading] " << SUCCESS << "Loaded."; FLUSH;
}

void NODES::SCRIPT::unloadDLL(HINSTANCE& dynlib) {
	if (dynlib != NULL) {
		FreeLibrary(dynlib);
	}
}

NODES::SCRIPT::Script* NODES::SCRIPT::loadScript(const QString& dll_path) {
	Script* script = nullptr;
	HINSTANCE script_addr = nullptr;

	loadDLL(script_addr, dll_path);
	FARPROC script_address = GetProcAddress(script_addr, "scriptInstance");
	if (script_address) {
		LOG++;
		Script* (*getInstance)(Session*) = (Script * (*)(Session*))script_address;
		script = getInstance(SESSION);
		if (script) {
			script->path = dll_path;

			script->onLoad();
			FILE.scripts.push(script);
			FILE.dlls[script] = script_addr;
		}
		LOG--;
	}

	return script;
}

void NODES::SCRIPT::reloadScript(Script* script) {
}

void NODES::SCRIPT::unloadScript(Script* script) {
	HINSTANCE script_addr = FILE.dlls[script];

	script->onUnload();

	for (U64 i = 0; i < FILE.nodes.size() ; i++) {
		auto res = FILE.nodes.cpy(i);
		if (res.get() == script) {
			FILE.nodes.removeIndex(i);
			break;
		}
	}

	unloadDLL(script_addr);
}

void NODES::SCRIPT::unloadScripts() {
	for (U64 i = 0; i < FILE.scripts.size(); i++) {
		NODES::SCRIPT::unloadScript(FILE.scripts.ptr(i));
	}
	FILE.dlls.clear();
	FILE.scripts.clear();
}

void NODES::SCRIPT::Script::execAllDownstream() const {
	for (const Port* port : outputs) {
		if (port->type() == Graphics_Item_Type::E_EXEC_O) {
			static_cast<const PORT::Exec_O*>(port)->exec();
		}
	}
}

bool NODES::SCRIPT::Script::missingInputs() const {
	for (const Port* port : inputs) {
		if (!port->connected()) {
			return true;
		}
	}
	return false;
}

void NODES::SCRIPT::Script::exec(const Port* port) {
	exec(static_cast<const PORT::Exec_I*>(port));
}

Ptr_S<Variable> NODES::SCRIPT::Script::getData(const Port* port) {
	return getData(static_cast<const PORT::Data_O*>(port));
}

void NODES::SCRIPT::Script::exec(const PORT::Exec_I* port) {
	execAllDownstream();
}

Ptr_S<Variable> NODES::SCRIPT::Script::getData(const PORT::Data_O* port) {
	return nullptr;
}

void NODES::SCRIPT::Script::saveDetail(CORE::Lace& lace) const {
	lace NL << path;
}