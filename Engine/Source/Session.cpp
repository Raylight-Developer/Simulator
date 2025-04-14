#include "Session.hpp"

#include "Window.hpp"
#include "Viewport.hpp"
#include "Scripting.hpp"

Session* Session::session_ptr = nullptr;

void Session::initialize(Session* session) {
	if (!session_ptr) {
		session_ptr = session;
	}
}

void Session::destroy() {
	delete session_ptr;
	session_ptr = nullptr;
}

Session::Session() :
	CORE::Session(),
	major_version(0),
	minor_version(0),
	patch_version(1),
	file(File()),
	gl(nullptr),
	window(nullptr),
	viewport(nullptr)
{
	current_frame = 0;
	samples = 60;
	active = false;
	realtime = false;
	start = NOW;
}