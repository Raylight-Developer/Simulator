#include "Session.hpp"

#include "Window.hpp"
#include "Scripting.hpp"

Session::Session() :
	KL::Session()
{}

Session& Session::getInstance() {
	static Session instance;
	return instance;
}