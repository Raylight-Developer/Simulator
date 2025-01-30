#include "Session.hpp"

#include "Window.hpp"
#include "Scripting.hpp"

CORE::Session::Session() :
	log(nullptr)
{}

CORE::Session& CORE::Session::getInstance() {
	static Session instance;
	return instance;
}

void CORE::Session::flushLog() {
	cout << log.str();
	log.clear();
}