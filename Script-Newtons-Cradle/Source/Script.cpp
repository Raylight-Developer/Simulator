#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Newton Script", session) {
	initialized = false;
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(140);
	rect.setHeight(60);

	ei_exec = EXEC_I("");
	eo_exec = EXEC_O("");

	SIM_HOOK.onInit[this] = [this]() {
		cradle.init();
		initialized = true;
	};

	LOGL(<< "Loaded Newton Script");
}

void Script::onUnload() {
	SIM_HOOK.onInit.remove(this);

	LOGL(<< "Unloaded Newton Script");
}

constexpr F64 MS_60FPS = 1.0 / 60.0;

void Script::exec(const Exec_I* port) {
	if (!initialized) {
		cradle.init();
		initialized = true;
	}
	F64 delta_time = MS_60FPS;
	if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME) {
		delta_time = min(SIM_HOOK.delta_time, MS_60FPS);
	}
	else {
		delta_time = SIM_HOOK.playback_delta_time;
	}
	cradle.exec(delta_time);

	execAllDownstream();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return make_shared<Variable>();
}