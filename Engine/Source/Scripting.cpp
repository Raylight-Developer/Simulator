#include "Scripting.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

NODES::SCRIPT::SCRIPT_LAYER::SL_Session::SL_Session(Script* script, Session* session) :
	session(session)
{}

KL::Lace& NODES::SCRIPT::SCRIPT_LAYER::SL_Session::log() const {
	return session->buffer;
}

KL::Lace& NODES::SCRIPT::SCRIPT_LAYER::SL_Session::printer() const {
	return session->printer;
}

QOpenGLFunctions_4_5_Core* NODES::SCRIPT::SCRIPT_LAYER::SL_Session::gl() const {
	return session->gl;
}

uvec2 NODES::SCRIPT::SCRIPT_LAYER::SL_Session::viewportResolution() const {
	return session->viewport->resolution;
}

dvec1 NODES::SCRIPT::SCRIPT_LAYER::SL_Session::viewport2DZoom() const {
	return session->viewport->zoom_2d;
}

dvec2 NODES::SCRIPT::SCRIPT_LAYER::SL_Session::viewport2DCenter() const {
	return session->viewport->center_2d;
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

NODES::SCRIPT::Script* NODES::SCRIPT::loadScript(const QString& dll_path) {
	Script* script = nullptr;
	HINSTANCE script_addr = nullptr;

	loadDLL(script_addr, dll_path);
	FARPROC script_address = GetProcAddress(script_addr, "scriptInstance");
	if (script_address) {
		Script* (*getInstance)(Session*) = (Script* (*)(Session*))script_address;
		script = getInstance(SESSION);

		//script->session = new SCRIPT_LAYER::SL_Session(script, &SESSION);
		//script->session = &SESSION;

		SESSION->scripts.push(script);
		SESSION->dlls[script] = script_addr;
		script->onLoad();
	}
	return script;
}

void NODES::SCRIPT::reloadScript(Script* script) {
}

void NODES::SCRIPT::unloadScript(Script* script) {
	HINSTANCE script_addr = SESSION->dlls[script];

	script->onUnload();
	SESSION->dlls.remove(script);
	SESSION->scripts.removeDelete(script); // TEST if Delete
	unloadDLL(script_addr);
}