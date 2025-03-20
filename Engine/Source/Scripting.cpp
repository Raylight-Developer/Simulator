#include "Scripting.hpp"

#include "Session.hpp"

NODES::SCRIPT::SCRIPT_LAYER::SL_Session::SL_Session(Script* script, Session* session) :
	session(session)
{}

KL::Lace& NODES::SCRIPT::SCRIPT_LAYER::SL_Session::log() {
	return session->buffer;
}

void NODES::SCRIPT::SCRIPT_LAYER::SL_Session::flush() {
	session->flushLog();
}

NODES::SCRIPT::Script::Script(const QString& id) :
	Node(id),
	session(nullptr)
{}

NODES::SCRIPT::Script::~Script() {
	delete session;
}

void NODES::SCRIPT::loadDLL(HINSTANCE& dynlib, const QString& dll_path) {
	const string dll_str = dll_path.toStdString();
	wstring stemp = wstring(dll_str.begin(), dll_str.end());
	LPCWSTR file_path = stemp.c_str();
	LOG NL << "[DLL Loading] Loading: " << dll_str; FLUSH;
	dynlib = LoadLibrary(file_path);
	if (!dynlib) {
		const unsigned int errorCode = static_cast<unsigned int>(GetLastError());
		LOG NL <<"[DLL Loading] LoadLibrary " << ERROR("Failed") << " with error code : " << errorCode; FLUSH;
		exit(EXIT_FAILURE);
	}
	LOG NL << "[DLL Loading] " << SUCCESS("Loaded."); FLUSH;
}

void NODES::SCRIPT::unloadDLL(HINSTANCE& dynlib) {
	if (dynlib != NULL) {
		FreeLibrary(dynlib);
	}
}

void NODES::SCRIPT::loadScript(const QString& dll_path) {
	Script* script = nullptr;
	HINSTANCE script_addr = nullptr;

	loadDLL(script_addr, dll_path);
	FARPROC script_address = GetProcAddress(script_addr, "scriptInstance");
	if (script_address) {
		Script* (*getInstance)() = (Script* (*)())script_address;
		script = getInstance();

		script->session = new SCRIPT_LAYER::SL_Session(script, &SESSION);

		SESSION.scripts[dll_path] = script;
		SESSION.dlls[script] = script_addr;
		script->onLoad();
	}
}

void NODES::SCRIPT::reloadScript(const QString& dll_path) {
}

void NODES::SCRIPT::unloadScript(const QString& dll_path) {
	Script* script = SESSION.scripts[dll_path];
	HINSTANCE script_addr = SESSION.dlls[script];

	script->onUnload();
	unloadDLL(script_addr);
	SESSION.dlls.remove(script);
	SESSION.scripts.remove(dll_path);
}