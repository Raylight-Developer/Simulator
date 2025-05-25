#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Camera Controller", session) {
	SCRIPT_INIT;
	// TODO zoom under mouse
	// TODO sensitivity input
}

void Script::onLoad() {
	rect.setWidth(180);
	rect.setHeight(60);

	ei_exec = EXEC_I("");

	eo_exec = EXEC_O("");

	panning = false;
	SESSION->hook.onWheel[this] = [this](const F64_V2& angle) {
		if (angle.y > 0.0) {
			SESSION->hook.camera_zoom_2d *= (1.15);
		}
		else if (angle.y < 0.0) {
			SESSION->hook.camera_zoom_2d /= (1.15);
		}
	};
	SESSION->hook.onKeyUp[this] = [this](const string& key) {
		if (key == "M Right") {
			panning = false;
		}
	};
	SESSION->hook.onKeyDown[this] = [this](const string& key) {
		if (key == "M Right") {
			last_pos = SESSION->hook.mouse_pos;
			panning = true;
		}
	};
	SESSION->hook.onInit[this] = [this]() {
		SESSION->hook.camera_pos_2d = F64_V2(0.0, 0.0);
		SESSION->hook.camera_zoom_2d = SESSION->hook.pixel_ratio * 5.0;
	};

	LOGL(<< "Loaded Camera Controller Script");
}

void Script::onUnload() {
	SESSION->hook.onWheel.remove(this);
	SESSION->hook.onKeyUp.remove(this);
	SESSION->hook.onKeyDown.remove(this);
	SESSION->hook.onInit.remove(this);

	LOGL(<< "Unloaded Camera Controller Script");
}

void Script::exec(const Exec_I* port) {
	if (SESSION->hook.mouse_on_screen) {
		if (panning) {
			const F64_V2 delta = last_pos - SESSION->hook.mouse_pos;
			SESSION->hook.camera_pos_2d += F64_V2(-delta.x, delta.y) / SESSION->hook.camera_zoom_2d;
			last_pos = SESSION->hook.mouse_pos;
		}
	}

	eo_exec->exec();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return nullptr;
}