#include "Scripting.hpp"

#include "Session.hpp"

#define SOLUTION_DIR string("D:/Simulator/")

#ifdef _DEBUG
	#define BUILD_DIR (std::filesystem::current_path().parent_path().string() + "/x64/Debug/")
#else
	#define BUILD_DIR (std::filesystem::current_path().parent_path().string() + "/x64/Release/")
#endif

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

void CORE::Script_Manager::loadDLL(HINSTANCE& dynlib, const string& path) {
	wstring stemp = wstring(path.begin(), path.end());
	LPCWSTR file_path = stemp.c_str();
	LOG ENDL ANSI_PURPLE << "[DLL Loading]" ANSI_RESET << " Loading: " << path << "..."; FLUSH;
	dynlib = LoadLibrary(file_path);
	if (!dynlib) {
		const unsigned int errorCode = static_cast<unsigned int>(GetLastError());
		LOG ENDL ANSI_R << "[DLL Loading]" ANSI_RESET << " LoadLibrary failed with error code:  " << errorCode; FLUSH;
		exit(EXIT_FAILURE);
	}
	LOG ENDL ANSI_G << "[DLL Loading]" ANSI_RESET << " Loaded."; FLUSH;
}

void CORE::Script_Manager::unloadDLL(HINSTANCE& dynlib) {
	if (dynlib != NULL) {
		FreeLibrary(dynlib);
	}
}