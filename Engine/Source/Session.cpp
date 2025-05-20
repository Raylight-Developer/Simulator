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
	viewport_resolution = F64_V2(1920.0, 1080.0);
	camera_pos_2d = F64_V2(0.0, 0.0);
	camera_zoom_2d = 1.0;
	pixel_ratio = 1.0;
	delta_time = 1.0 / 60.0;
	exec_time = 0.0;

	mouse_pos = F64_V2(980.0, 540.0);
	mouse_on_screen = false;
	mouse_wheel = { 0, 0 };

	playback_delta_time = 1.0 / 60.0;
	playback_start = NOW;
	playback_mode = Playback_Mode::REALTIME;
	current_frame = 0;
	samples = 60;
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
{}