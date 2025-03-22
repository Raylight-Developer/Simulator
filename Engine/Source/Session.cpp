#include "Session.hpp"

#include "Window.hpp"
#include "Scripting.hpp"

Session::Session() :
	KL::Session(),
	file(File())
{}

Session& Session::getInstance() {
	static Session instance;
	return instance;
}