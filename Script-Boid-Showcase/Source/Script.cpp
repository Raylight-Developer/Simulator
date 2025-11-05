#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Boids", session), initialized(false), boid_system(BoidSystem(50)) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(160);
	rect.setHeight(160);

	ei_exec = EXEC_I("");

	di_runtime   = DATA_I("Runtime", Variable(0.0));
	di_path_size = DATA_I("Path Size", Variable(3.0));
	di_path_weight = DATA_I("Path Weight", Variable(5.0));

	eo_exec = EXEC_O("");

#ifdef _DEBUG
	samples = 1;
	count = 64;
#else
	samples = 1;
	count = 1024;
#endif

	SIM_HOOK.onInit[this] = [this]() {
		boid_system = BoidSystem(count);
		initialized = true;
	};

	LOGL(<< "Loaded Boid Showcase Script");
}

void Script::onUnload() {
	SIM_HOOK.onInit.remove(this);

	LOGL(<< "Unloaded Boid Showcase Script");
}

constexpr F64 MS_60FPS = 1.0 / 60.0;

void Script::exec(const Exec_I* port) {
	if (!initialized) {
		boid_system = BoidSystem(count);
		initialized = true;
	}

	boid_system.pathSize = *di_path_size->GET_DATA(F64);
	boid_system.pathWeight = *di_path_weight->GET_DATA(F64);

	F64 delta_time = MS_60FPS;
	if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME) {
		delta_time = min(SIM_HOOK.delta_time, MS_60FPS) * 5.0;
	}
	else {
		delta_time = SIM_HOOK.playback_delta_time * 5.0;
	}
	delta_time /= samples;

	// Euler Integration O(n)
	for (U32 sample = 0; sample < samples; sample++) {
		boid_system.update(delta_time);
	}

	for (U32 i = 0; i < count; i++) {
		const F64 hue = fmod((360.0 * i) / count, 360.0); // evenly spaced hue

		const auto& boids = boid_system.getBoids();

		const F64_V3 pos = boids[i].position;
		const F64_M4 rotation = glm::eulerAngleXYZ(0.0, glm::radians(*di_runtime->GET_DATA(F64) * 10.0), 0.0);
		const F64_V4 rotated = rotation * F64_V4(pos, 1.0);
		RENDER::Dim_3D::Sphere(xyz(rotated), 0.2f, Color::HSV(hue, 1.0, 1.0));
	}

	eo_exec->exec();
}