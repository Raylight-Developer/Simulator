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
	hook(Hook()),
	gl(nullptr),
	window(nullptr),
	viewport(nullptr)
{
	samples = 60;
	playback_mode = Playback_Mode::REALTIME;

	hook.playback_start = NOW;
	hook.current_frame = 0;
}