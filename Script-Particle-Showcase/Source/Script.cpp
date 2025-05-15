#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Particles", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(140);
	rect.setHeight(120);

	ei_exec = EXEC_I("");
	di_effector_pos = DATA_I("Effector Pos", Variable(F64_V2(0,0)));
	di_effector_vel = DATA_I("Effector Vel", Variable(F64_V2(0,0)));
	di_effector_rad = DATA_I("Effector Rad", Variable(0.0));

	eo_exec = EXEC_O("");

	samples = 4;
#ifdef _DEBUG
	count = 64;
#else
	count = 512;
#endif
	radius = 10.0;
	terminal = 50.0;
	restitution = 0.95;
	gravity = F64_V2(0.0, -9.81);

	x_bounds = F64_V2(-600, 600);
	y_bounds = F64_V2(-400, 400);

	SESSION->hook.onInit[this] = [this]() {
		positions.clear();
		positions.assign(count, F64_V2(0.0, 0.0));

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
	F64 delta_time = MS_60FPS;
	if (SESSION->hook.playback_mode == Playback_Mode::REALTIME) {
		delta_time = (SESSION->hook.delta_time > MS_60FPS ? MS_60FPS : SESSION->hook.delta_time) * 25.0;
	}
	else {
		delta_time = SESSION->hook.playback_delta_time * 25.0;
	}
	delta_time /= samples;

	// Euler Integration O(n)
	for (U32 sample = 0; sample < samples; sample++) {
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
			// Check for Effector Collisions
			for (U32 j = i + 1; j < count; ++j) {
				circleDynamicCollision(positions.ref(i), positions.ref(j), velocities.ref(i), velocities.ref(j), radius, radius, 1.0, 1.0, restitution);
			}
			if (di_effector_pos->connected() && di_effector_rad->connected() && di_effector_vel->connected()) {
				const F64_V2 effector_pos = *di_effector_pos->GET_DATA(F64_V2);
				const F64_V2 effector_vel = *di_effector_vel->GET_DATA(F64_V2);
				const F64 effector_rad = *di_effector_rad->GET_DATA(F64);

				circleStaticCollision(positions.ref(i), effector_pos, velocities.ref(i), effector_vel, radius, effector_rad, 1.0, 10.0, restitution);
			}
		}
	}

	for (U32 i = 0; i < count; i++) {
		const F64 hue = fmod((360.0 * i) / count, 360.0);  // evenly spaced hue
		RENDER::Dim_2D::Circle(positions.ref(i), radius, Color::HSV(hue, 1.0f, 1.0f));
	}

	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x - 2.5, y_bounds.x - 2.5), F64_V2(x_bounds.y + 2.5, y_bounds.x - 2.5), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x - 2.5, y_bounds.y + 2.5), F64_V2(x_bounds.y + 2.5, y_bounds.y + 2.5), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.x - 2.5, y_bounds.x - 2.5), F64_V2(x_bounds.x - 2.5, y_bounds.y + 2.5), 5.0);
	RENDER::Dim_2D::RoundedLine(F64_V2(x_bounds.y + 2.5, y_bounds.x - 2.5), F64_V2(x_bounds.y + 2.5, y_bounds.y + 2.5), 5.0);

	eo_exec->exec();
}

F64_V2 randomUnitVector() {
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<F64> dist(0.0, 2.0 * glm::pi<F64>());

	F64 angle = dist(rng);
	return F64_V2(glm::cos(angle), glm::sin(angle));
}

void circleDynamicCollision(F64_V2& pos_a, F64_V2& pos_b, F64_V2& vel_a, F64_V2& vel_b, const F64& rad_a, const F64& rad_b, const F64& mass_a, const F64& mass_b, const F64& restitution) {
	const F64_V2 delta = pos_b - pos_a;
	const F64 dist2 = glm::length2(delta);
	const F64 radii = rad_a + rad_b;

	if (dist2 > radii * radii) {
		return;
	}

	const F64_V2 normal = (dist2 == 0.0) ? randomUnitVector() : glm::normalize(delta);
	const F64_V2 rel_vel = vel_b - vel_a;

	const F64 vel_along_normal = glm::dot(rel_vel, normal);
	if (vel_along_normal > 0) {
		return;
	}

	const F64 inv_mass_a = (mass_a > 0) ? 1.0 / mass_a : 0.0;
	const F64 inv_mass_b = (mass_b > 0) ? 1.0 / mass_b : 0.0;

	const F64 j = ( - (1.0 + restitution) * vel_along_normal) / (inv_mass_a + inv_mass_b);

	const F64_V2 impulse = j * normal;

	vel_a -= impulse * inv_mass_a;
	vel_b += impulse * inv_mass_b;

	// Positional correction
	const F64 penetration = radii - ((dist2 == 0.0) ? 0.0 : glm::sqrt(dist2));
	if (penetration > 0.01) {
		const F64 percent = 0.8;
		const F64_V2 correction = (penetration / (inv_mass_a + inv_mass_b)) * percent * normal;

		pos_a -= correction * inv_mass_a;
		pos_b += correction * inv_mass_b;
	}
}

void circleStaticCollision(F64_V2& pos_a, const F64_V2& pos_b, F64_V2& vel_a, const F64_V2& vel_b, const F64& rad_a, const F64& rad_b, const F64& mass_a, const F64& mass_b, const F64& restitution) {
	const F64_V2 delta = pos_a - pos_b;
	const F64 dist2 = glm::length2(delta);
	const F64 radii = rad_a + rad_b;

	if (dist2 > radii * radii) {
		return;
	}

	const F64_V2 normal = (dist2 == 0.0) ? randomUnitVector() : glm::normalize(delta);

	// Include vel_b to get relative velocity
	const F64_V2 rel_vel = vel_a - vel_b;
	const F64 vel_along_normal = glm::dot(rel_vel, normal);
	if (vel_along_normal > 0) {
		return;
	}

	// Calculate impulse (only affects A)
	const F64 j = -(1.0 + restitution) * vel_along_normal;
	const F64 inv_mass_a = (mass_a > 0.0) ? 1.0 / mass_a : 0.0;

	vel_a += j * normal * inv_mass_a;

	// Positional correction (only A is moved)
	const F64 penetration = radii - ((dist2 == 0.0) ? 0.0 : glm::sqrt(dist2));
	if (penetration > 0.01) {
		const F64 percent = 0.8;
		if (mass_a > 0) {
			F64_V2 correction = (penetration / inv_mass_a) * percent * normal;
			pos_a += correction;
		}
	}
}