#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Particles", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(120);
	rect.setHeight(60);

	ei_exec = EXEC_I("");

	eo_exec = EXEC_O("");

	count = 64;
	radius = 10.0;
	terminal = 50.0;
	restitution = 0.95;
	gravity = F64_V2(0.0, -9.81);

	x_bounds = F64_V2(-640, 640);
	y_bounds = F64_V2(-400, 400);

	SESSION->hook.onInit[this] = [this]() {
		positions.clear();
		positions.reserve(count);
		const F64 spacing = 1.1;
		const F64 halfSize = (radius * 2.0 - 1) * spacing * 0.5;
		for (int y = 0; y < 8; ++y) {
			for (int x = 0; x < 8; ++x) {
				const F64 px = x * spacing - halfSize;
				const F64 py = y * spacing - halfSize;
				positions.emplace(px, py);
			}
		}

		velocities.clear();
		velocities.assign(count, F64_V2(0.0, 0.0));
	};

	LOGL(<< "Loaded Particle Showcase Script");
}

void Script::onUnload() {
	SESSION->hook.onInit.remove(this);

	LOGL(<< "Unloaded Particle Showcase Script");
}

constexpr F64 MS_60FPS = 1.0 / 60.0;

void Script::exec(const Exec_I* port) {
	const F64 delta_time = (SESSION->hook.playback_mode == Playback_Mode::REALTIME) ?
		((SESSION->hook.delta_time > MS_60FPS ? MS_60FPS : SESSION->hook.delta_time) * 25.0) :
		(SESSION->hook.playback_delta_time);

	// Euler Integration O(n)
	for (U32 i = 0; i < count; ++i) {
		velocities.ref(i).x += gravity.x * delta_time;
		velocities.ref(i).y += gravity.y * delta_time;

		const F64 vx = velocities.ref(i).x;
		const F64 vy = velocities.ref(i).y;
		const F64 speed = std::sqrt(vx * vx + vy * vy);

		if (speed > terminal) {
			double scale = terminal / speed;
			velocities.ref(i).x *= scale;
			velocities.ref(i).y *= scale;
		}

		positions.ref(i).x += velocities.ref(i).x * delta_time;
		positions.ref(i).y += velocities.ref(i).y * delta_time;

		// Bounding Collisions
		if (positions.ref(i).x - radius < x_bounds.x) {
			positions.ref(i).x = x_bounds.x + radius;
			velocities.ref(i).x *= -1.0 * restitution;
		}
		if (positions.ref(i).x + radius > x_bounds.y) {
			positions.ref(i).x = x_bounds.y - radius;
			velocities.ref(i).x *= -1.0 * restitution;
		}
		if (positions.ref(i).y - radius < y_bounds.x) {
			positions.ref(i).y = y_bounds.x + radius;
			velocities.ref(i).y *= -1.0 * restitution;
		}
		if (positions.ref(i).y + radius > y_bounds.y) {
			positions.ref(i).y = y_bounds.y - radius;
			velocities.ref(i).y *= -1.0 * restitution;
		}
	}

	// Check and resolve self-collisions O(n^2)
	for (U32 i = 0; i < count; ++i) {
		for (U32 j = i + 1; j < count; ++j) {
			const F64 dx = positions.ref(j).x - positions.ref(i).x;
			const F64 dy = positions.ref(j).y - positions.ref(i).y;
			const F64 dist2 = dx * dx + dy * dy;
			const F64 minDist = 2 * radius;
			if (dist2 < minDist * minDist && dist2 > 0.0) {
				const F64 dist = std::sqrt(dist2);
				const F64 nx = dx / dist;
				const F64 ny = dy / dist;

				// Push particles apart (equal displacement)
				const F64 overlap = 0.5 * (minDist - dist);
				positions.ref(i).x -= nx * overlap;
				positions.ref(i).y -= ny * overlap;
				positions.ref(j).x += nx * overlap;
				positions.ref(j).y += ny * overlap;

				// Reflect velocities along collision normal (simplified elastic)
				const F64 vi_n = velocities.ref(i).x * nx + velocities.ref(i).y * ny;
				const F64 vj_n = velocities.ref(j).x * nx + velocities.ref(j).y * ny;

				// Swap normal components
				const F64 vi_n_new = vj_n * restitution;
				const F64 vj_n_new = vi_n * restitution;

				// Update velocities
				velocities.ref(i).x += (vi_n_new - vi_n) * nx;
				velocities.ref(i).y += (vi_n_new - vi_n) * ny;
				velocities.ref(j).x += (vj_n_new - vj_n) * nx;
				velocities.ref(j).y += (vj_n_new - vj_n) * ny;
			}
		}
	}

	for (const auto& pos : positions) {
		RENDER::Dim_2D::Circle(pos, radius);
	}

	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x, y_bounds.x - 2.5), F64_V2(x_bounds.y, y_bounds.x - 2.5), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x, y_bounds.y + 2.5), F64_V2(x_bounds.y, y_bounds.y + 2.5), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x - 2.5, y_bounds.x), F64_V2(x_bounds.x - 2.5, y_bounds.y), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.y + 2.5, y_bounds.x), F64_V2(x_bounds.y + 2.5, y_bounds.y), 5.0);

	eo_exec->exec();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return nullptr;
}