#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Camera Controller", session) {
	SCRIPT_INIT;
	// TODO zoom under mouse
	// TODO view_sensitivity input
}

void Script::onLoad() {
	rect.setWidth(180);
	rect.setHeight(60);

	ei_exec = EXEC_I("");

	eo_exec = EXEC_O("");

	panning = false;

	mode_3d = false;
	orbiting = false;
	first_person = false;

	SIM_HOOK.onInit[this] = []() {
		SIM_HOOK.camera_pos_2d = F64_V2(0.0, 0.0);
		SIM_HOOK.camera_zoom_2d = SIM_HOOK.pixel_ratio * 5.0;

		SIM_HOOK.camera_3d.position = F64_V3(7.5, 2.5, 7.5);
		SIM_HOOK.camera_3d.target   = F64_V3(0.0, 0.0, 0.0);
	};
	SIM_HOOK.onWheel[this] = [this](const F64_V2& angle) {
		if (mode_3d) {

		}
		else {
			if (angle.y > 0.0) {
				SIM_HOOK.camera_zoom_2d *= (1.15);
			}
			else if (angle.y < 0.0) {
				SIM_HOOK.camera_zoom_2d /= (1.15);
			}
		}
	};
	SIM_HOOK.onKeyUp[this] = [this](const string& key) {
		if (mode_3d) {
			if (key == "M Right") {
				first_person = false;
				orbiting = false;
			}
			else if (key == "M Left") {
				orbiting = false;
			}
		}
		else {
			if (key == "M Right") {
				panning = false;
			}
		}
	};
	SIM_HOOK.onKeyDown[this] = [this](const string& key) {
		if (mode_3d) {
			if (key == "M Right") {
				last_pos = SIM_HOOK.mouse_pos;

				if (SIM_HOOK.input_down["Alt"]) {
					orbiting = true;
				}
				else {
					first_person = true;
				}
			}
			else if (key == "M Left" && SIM_HOOK.input_down["Alt"]) {
				last_pos = SIM_HOOK.mouse_pos;
				orbiting = true;
			}
		}
		else {
			if (key == "M Right") {
				last_pos = SIM_HOOK.mouse_pos;
				panning = true;
			}
		}

		if (key == "2") {
			mode_3d = false;
		}
		else if (key == "3") {
			mode_3d = true;
		}
	};
	SIM_HOOK.onGuiRender[this] = [this](QPainter* painter) {
		painter->setPen(Qt::white);
		if (mode_3d) {
			painter->drawText(20, 40, "3D Controller");
		}
		else {
			painter->drawText(20, 40, "2D Controller");
		}
	};

	LOGL(<< "Loaded Camera Controller Script");
}

void Script::onUnload() {
	SIM_HOOK.onInit.remove(this);
	SIM_HOOK.onWheel.remove(this);
	SIM_HOOK.onKeyUp.remove(this);
	SIM_HOOK.onKeyDown.remove(this);
	SIM_HOOK.onGuiRender.remove(this);

	LOGL(<< "Unloaded Camera Controller Script");
}

void Script::exec(const Exec_I* port) {
	const F64 delta = SIM_HOOK.getDeltaTime();

	if (SIM_HOOK.mouse_on_screen) {
		const F64_V2 mouse_delta = last_pos - SIM_HOOK.mouse_pos;
		last_pos = SIM_HOOK.mouse_pos;

		const F64 view_sensitivity = 0.25;
		const F64 move_sensitivity = 5.0;
		if (panning) {
			SIM_HOOK.camera_pos_2d += F64_V2(-mouse_delta.x, mouse_delta.y) / SIM_HOOK.camera_zoom_2d;
		}
		else if (orbiting) {
			SIM_HOOK.camera_3d.orbit(mouse_delta.y * view_sensitivity, -mouse_delta.x * view_sensitivity);
		}
		else if (first_person) {
			SIM_HOOK.camera_3d.rotate(-mouse_delta.y * view_sensitivity, -mouse_delta.x * view_sensitivity);
		}
		if (mode_3d) {
			if (SIM_HOOK.input_down["W"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3(0,0, 1));
			}
			if (SIM_HOOK.input_down["S"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3(0,0,-1));
			}
			if (SIM_HOOK.input_down["D"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3( 1,0,0));
			}
			if (SIM_HOOK.input_down["A"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3(-1,0,0));
			}
			if (SIM_HOOK.input_down["E"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3(0, 1,0));
			}
			if (SIM_HOOK.input_down["Q"]) {
				SIM_HOOK.camera_3d.translate(delta * move_sensitivity * F64_V3(0,-1,0));
			}
		}
	}

	eo_exec->exec();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return nullptr;
}