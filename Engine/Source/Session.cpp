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

Hook::Hook() {
	viewport_resolution = F64_V2(1920, 1080);
	mouse_pos = F64_V2(980, 540);
	mouse_on_screen = false;
	mouse_wheel = { 0, 0 };

	playback_start = NOW;
	current_frame = 0;
}

Session::Session() :
	CORE::Session(),
	major_version(0),
	minor_version(0),
	patch_version(1),
	hook(Hook()),
	file(File()),
	gl(nullptr),
	window(nullptr),
	viewport(nullptr)
{
	samples = 60;
	playback_mode = Playback_Mode::REALTIME;
}