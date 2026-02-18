#pragma once

#include "Script_Include.hpp"

const F64 GRAVITY = 98.1;  // pixels/s^2
const F64 DAMPING = 0.9995;  // Very slight damping for realism
const F64 COLLISION_RESTITUTION = 0.999;  // Nearly elastic collisions

struct Pendulum {
	F32_V2 pivot;        // Fixed pivot point
	F64 length;          // String length
	F64 radius;          // Ball radius
	F64 angle;           // Current angle from vertical (radians)
	F64 angularVelocity; // Angular velocity (rad/s)
	F64 mass;            // Mass (for momentum calculations)

	F32_V2 getPosition() const {
		// Correct geometry: balls hang DOWN from pivot
		return F32_V2(
			pivot.x + length * std::sin(angle),
			pivot.y + length * std::cos(angle)
		);
	}

	F64 getVelocityX() const {
		return angularVelocity * length * std::cos(angle);
	}
};

struct NewtonsCradle {
	std::vector<Pendulum> pendulums;
	F64 pivotY;
	F64 stringLength;
	F64 ballRadius;
	int numBalls;

	void init() {
		numBalls = 10;
		pivotY = 0.0;  // Pivot at top
		stringLength = 30.0;
		ballRadius = 3.0;

		F64 spacing = ballRadius * 2.0;
		F64 centerX = 0.0;
		F64 startX = centerX - (numBalls - 1) * spacing * 0.5;

		pendulums.clear();
		for (int i = 0; i < numBalls; i++) {
			Pendulum p;
			p.pivot = F32_V2(startX + i * spacing, pivotY);
			p.length = stringLength;
			p.radius = ballRadius;
			p.mass = 1.0;

			if (i == 0) {
				p.angle = -0.6;  // Start left ball raised
			}
			else {
				p.angle = 0.0;
			}
			p.angularVelocity = 0.0;

			pendulums.push_back(p);
		}
	}

	void exec(const F64& delta) {
		// Update physics with smaller substeps for stability
		const int substeps = 4;
		F64 substep_delta = delta / substeps;

		for (int s = 0; s < substeps; s++) {
			updatePendulums(substep_delta);
			handleCollisions();
		}

		// Draw the cradle
		draw();
	}

	void updatePendulums(const F64& delta) {
		for (auto& p : pendulums) {
			// Pendulum equation: angular_accel = -(g/L) * sin(angle)
			F64 angularAccel = -(GRAVITY / p.length) * std::sin(p.angle);

			p.angularVelocity += angularAccel * delta;
			p.angularVelocity *= DAMPING;
			p.angle += p.angularVelocity * delta;
		}
	}

	void handleCollisions() {
		for (size_t i = 0; i < pendulums.size() - 1; i++) {
			F32_V2 pos1 = pendulums[i].getPosition();
			F32_V2 pos2 = pendulums[i + 1].getPosition();

			F64 dx = pos2.x - pos1.x;
			F64 dy = pos2.y - pos1.y;
			F64 distance = std::sqrt(dx * dx + dy * dy);
			F64 minDist = pendulums[i].radius + pendulums[i + 1].radius;

			if (distance < minDist && distance > 0.0001) {
				// Get horizontal velocities
				F64 v1 = pendulums[i].getVelocityX();
				F64 v2 = pendulums[i + 1].getVelocityX();

				// Only collide if approaching
				if (v1 > v2) {
					// For equal masses, velocities simply exchange
					F64 v1_new = v2;
					F64 v2_new = v1;

					// Apply restitution
					v1_new *= COLLISION_RESTITUTION;
					v2_new *= COLLISION_RESTITUTION;

					// Convert back to angular velocities
					F64 cos1 = std::cos(pendulums[i].angle);
					F64 cos2 = std::cos(pendulums[i + 1].angle);

					if (std::abs(cos1) > 0.01) {
						pendulums[i].angularVelocity = v1_new / (pendulums[i].length * cos1);
					}
					if (std::abs(cos2) > 0.01) {
						pendulums[i + 1].angularVelocity = v2_new / (pendulums[i + 1].length * cos2);
					}

					// Separate overlapping balls
					F64 overlap = minDist - distance;
					F64 separationAngle = overlap / (2.0 * stringLength);

					pendulums[i].angle -= separationAngle;
					pendulums[i + 1].angle += separationAngle;
				}
			}
		}
	}

	void draw() {
		Color stringColor(0.6, 0.6, 0.6, 1.0);
		Color ballColor(0.8, 0.8, 0.9, 1.0);
		Color pivotColor(0.4, 0.4, 0.4, 1.0);

		// Draw frame/pivot bar
		F64 frameWidth = (numBalls - 1) * (ballRadius * 2.0) + 4.0;
		F32_V2 frameLeft(pendulums[0].pivot.x - 2.0, pivotY);
		F32_V2 frameRight(pendulums[numBalls - 1].pivot.x + 2.0, pivotY);
		RENDER::Dim_2D::RoundedLine(frameLeft, frameRight, 0.8, pivotColor, false);

		// Draw strings and balls
		for (const auto& p : pendulums) {
			F32_V2 ballPos = p.getPosition();
			ballPos.y = -ballPos.y;

			// Draw string
			RENDER::Dim_2D::RoundedLine(p.pivot, ballPos, 0.2, stringColor, false);

			// Draw pivot point
			RENDER::Dim_2D::Circle(p.pivot, 0.4, pivotColor, false);

			// Draw ball with shading
			RENDER::Dim_2D::Circle(ballPos, p.radius, ballColor, true);

			// Add highlight for 3D effect
			F32_V2 highlight = ballPos + F32_V2(-p.radius * 0.3, -p.radius * 0.3);
			RENDER::Dim_2D::Circle(highlight, p.radius * 0.3, Color(1.0, 1.0, 1.0, 0.6), true);
		}
	}
};

struct Script : SCRIPT {
	PORT_EXEC_I ei_exec;
	PORT_EXEC_O eo_exec;
	bool initialized = false;
	NewtonsCradle cradle;

	Script(Session* session);

	void onLoad() final override;
	void onUnload() final override;

	void exec(const Exec_I* port) final override;
	Ptr_S<Variable> getData(const Data_O* port) final override;
};