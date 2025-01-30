#include "Scripting.hpp"

#include "Session.hpp"

SCRIPT_LAYER::Session::Session(CORE::Script* script, CORE::Session* session) :
	session(session)
{}

CORE::Lace& SCRIPT_LAYER::Session::log() {
	return session->log;
}

void SCRIPT_LAYER::Session::flush() {
	session->flushLog();
}

CORE::Script::~Script() {
	delete session;
}
QRectF CORE::Script::boundingRect() const {
	return QRectF(-25, -25, 50, 50);
}

void CORE::Script::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->drawRect(boundingRect());
}

void CORE::Script_Manager::loadDLL(HINSTANCE& dynlib) {
	const string libfile = SOLUTION_DIR + "x64/Debug/Scripting/Scripting.dll";
	wstring stemp = wstring(libfile.begin(), libfile.end());
	LPCWSTR file_path = stemp.c_str();
	LOG ENDL ANSI_PURPLE << "[DLL Loading]" ANSI_RESET << " Loading: " << libfile << "..."; FLUSH;
	dynlib = LoadLibrary(file_path);
	if (!dynlib) {
		const unsigned int errorCode = static_cast<unsigned int>(GetLastError());
		LOG ENDL ANSI_R << "[DLL Loading]" ANSI_RESET << " LoadLibrary failed with error code:  " << errorCode; FLUSH;
		exit(EXIT_FAILURE);
	}
	LOG ENDL ANSI_G << "[DLL Loading]" ANSI_RESET << " Loaded."; FLUSH;
}

void CORE::Script_Manager::recompileDLL(HINSTANCE& dynlib) {
	unloadDLL(dynlib);

	Lace temp;
	temp << "C:/Programs/Coding/Microsoft/VisualStudio/Community/MSBuild/Current/Bin/MSBuild.exe";
	temp << " /t:Scripting";
	temp << " /p:Configuration=Release";
	temp << " /p:Platform=x64";
	temp << " /v:quiet";
	temp << " \"" << SOLUTION_DIR << "Trader.sln\"";
	const string rebuildCommand = temp.str();
	const int result = system(rebuildCommand.c_str());
	if (result == 0) {
		LOG ENDL ANSI_G << "[DLL Compilation]" ANSI_RESET << " Succesfully Compiled."; FLUSH;
	}
	else {
		LOG ENDL ANSI_R << "[DLL Compilation]" ANSI_RESET << " Compilation Failed."; FLUSH;
	}

	loadDLL(dynlib);
}

void CORE::Script_Manager::unloadDLL(HINSTANCE& dynlib) {
	if (dynlib != NULL) {
		FreeLibrary(dynlib);
	}
}