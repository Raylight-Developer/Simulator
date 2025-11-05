#pragma once

#include "Core/Script_Include.hpp"

class Boid {
public:
	F64_V3 position;
	F64_V3 velocity;
	F64_V3 acceleration;

	F64 maxSpeed;
	F64 maxForce;
	F64 separationRadius;
	F64 alignmentRadius;
	F64 cohesionRadius;

	Boid(F64_V3 pos) : position(pos), maxSpeed(2.0), maxForce(0.1),
		separationRadius(1.0f), alignmentRadius(2.0), cohesionRadius(2.0) {
		// Random initial velocity
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<F64> dis(-1.0, 1.0);

		velocity = F64_V3(dis(gen), dis(gen), dis(gen));
		velocity = glm::normalize(velocity) * maxSpeed * 0.5;
		acceleration = F64_V3(0.0f);
	}

	void update(F64 deltaTime) {
		// Update velocity and position
		velocity += acceleration * deltaTime;
		velocity = limit(velocity, maxSpeed);
		position += velocity * deltaTime;

		// Reset acceleration
		acceleration = F64_V3(0.0f);
	}

	void applyForce(const F64_V3& force) {
		acceleration += force;
	}

	// Get point on trefoil knot curve at parameter t
	static F64_V3 getTrefoilPoint(F64 t, F64 scale = 3.0) {
		// Trefoil knot parametric equations
		F64 x = scale * (sin(t) + 2.0 * sin(2.0 * t));
		F64 y = scale * (cos(t) - 2.0 * cos(2.0 * t));
		F64 z = scale * (-sin(3.0 * t)) * 0.8; // Scale Z a bit to make it less extreme
		return F64_V3(x, y, z);
	}

	// Get tangent vector (direction) on trefoil knot at parameter t
	static F64_V3 getTrefoilTangent(F64 t, F64 scale = 3.0f) {
		// Derivatives of trefoil parametric equations
		F64 dx = scale * (cos(t) + 4.0 * cos(2.0 * t));
		F64 dy = scale * (-sin(t) + 4.0 * sin(2.0 * t));
		F64 dz = scale * (-3.0f * cos(3.0 * t)) * 0.8;
		F64_V3 tangent(dx, dy, dz);
		return glm::length(tangent) > 0.001 ? glm::normalize(tangent) : F64_V3(1, 0, 0);
	}

	// Find closest point on trefoil knot curve
	F64 findClosestParameterOnTrefoil(const F64_V3& point, F64 scale = 3.0) {
		F64 minDist = std::numeric_limits<F64>::max();
		F64 bestT = 0.0;

		// Coarse sampling first
		for (int i = 0; i < 200; ++i) {
			F64 t = (F64)i / 200.0 * 2.0 * M_PI;
			F64_V3 curvePoint = getTrefoilPoint(t, scale);
			F64 dist = glm::distance2(point, curvePoint);

			if (dist < minDist) {
				minDist = dist;
				bestT = t;
			}
		}

		// Fine-tune with local search around best point
		F64 step = M_PI / 200.0;
		for (int i = 0; i < 10; ++i) {
			F64 t1 = bestT - step;
			F64 t2 = bestT + step;

			F64_V3 p1 = getTrefoilPoint(t1, scale);
			F64_V3 p2 = getTrefoilPoint(t2, scale);

			F64 d1 = glm::distance2(point, p1);
			F64 d2 = glm::distance2(point, p2);

			if (d1 < minDist) {
				minDist = d1;
				bestT = t1;
			}
			if (d2 < minDist) {
				minDist = d2;
				bestT = t2;
			}

			step *= 0.5f; // Reduce step size
		}

		return bestT;
	}

	// Force to follow trefoil knot path
	F64_V3 followPath(F64 scale = 3.0, F64 pathRadius = 2.0) {
		// Find closest point on trefoil curve
		F64 t = findClosestParameterOnTrefoil(position, scale);

		// Get current point on curve and tangent direction
		F64_V3 curvePoint = getTrefoilPoint(t, scale);
		F64_V3 pathDirection = getTrefoilTangent(t, scale);

		// Calculate distance from path
		F64 distanceFromPath = glm::distance(position, curvePoint);

		// If too far from path, steer towards it strongly
		if (distanceFromPath > pathRadius) {
			F64_V3 toPath = curvePoint - position;
			toPath = glm::normalize(toPath) * maxSpeed;
			F64_V3 steer = toPath - velocity;
			return limit(steer, maxForce * 2.5); // Strong force for path following
		}

		// Otherwise, follow path direction with gentle attraction to curve
		F64_V3 desired = pathDirection * maxSpeed;
		F64_V3 steer = desired - velocity;

		// Add gentle attraction to stay on path
		F64_V3 attraction = (curvePoint - position) * 0.2;
		steer += attraction;

		return limit(steer, maxForce);
	}

	// Flocking behaviors
	F64_V3 separate(const std::vector<Boid>& boids) {
		F64_V3 steer(0.0);
		int count = 0;

		for (const auto& other : boids) {
			F64 d = glm::distance(position, other.position);
			if (d > 0 && d < separationRadius) {
				F64_V3 diff = position - other.position;
				diff = glm::normalize(diff);
				diff /= d; // Weight by distance
				steer += diff;
				count++;
			}
		}

		if (count > 0) {
			steer /= F64(count);
			steer = glm::normalize(steer) * maxSpeed;
			steer = steer - velocity;
			return limit(steer, maxForce);
		}

		return F64_V3(0.0);
	}

	F64_V3 align(const std::vector<Boid>& boids) {
		F64_V3 sum(0.0);
		int count = 0;

		for (const auto& other : boids) {
			F64 d = glm::distance(position, other.position);
			if (d > 0 && d < alignmentRadius) {
				sum += other.velocity;
				count++;
			}
		}

		if (count > 0) {
			sum /= F64(count);
			sum = glm::normalize(sum) * maxSpeed;
			F64_V3 steer = sum - velocity;
			return limit(steer, maxForce);
		}

		return F64_V3(0.0);
	}

	F64_V3 cohesion(const std::vector<Boid>& boids) {
		F64_V3 sum(0.0);
		int count = 0;

		for (const auto& other : boids) {
			F64 d = glm::distance(position, other.position);
			if (d > 0 && d < cohesionRadius) {
				sum += other.position;
				count++;
			}
		}

		if (count > 0) {
			sum /= F64(count);
			return seek(sum);
		}

		return F64_V3(0.0);
	}

	// Forward-looking avoidance
	F64_V3 avoidObstacles(const std::vector<Boid>& boids, F64 lookAhead = 2.0) {
		F64_V3 ahead = position + glm::normalize(velocity) * lookAhead;
		F64_V3 ahead2 = position + glm::normalize(velocity) * lookAhead * 0.5;

		F64_V3 avoidance(0.0);

		for (const auto& other : boids) {
			if (glm::distance(other.position, position) < 0.1f) continue; // Skip self

			F64 d1 = glm::distance(other.position, ahead);
			F64 d2 = glm::distance(other.position, ahead2);
			F64 d3 = glm::distance(other.position, position);

			if (d1 <= separationRadius || d2 <= separationRadius || d3 <= separationRadius) {
				avoidance += ahead - other.position;
			}
		}

		if (glm::length2(avoidance) > 0) {
			avoidance = glm::normalize(avoidance) * maxSpeed;
			avoidance = avoidance - velocity;
			return limit(avoidance, maxForce * 1.5);
		}

		return F64_V3(0.0f);
	}

private:
	F64_V3 seek(const F64_V3& target) {
		F64_V3 desired = target - position;
		desired = glm::normalize(desired) * maxSpeed;
		F64_V3 steer = desired - velocity;
		return limit(steer, maxForce);
	}

	F64_V3 limit(const F64_V3& vec, F64 max) {
		if (glm::length2(vec) > max * max) {
			return glm::normalize(vec) * max;
		}
		return vec;
	}
};

struct BoidSystem {
	std::vector<Boid> boids;

	// Behavior weights
	F64 separationWeight = 2.0;
	F64 avoidanceWeight = 2.5;
	F64 alignmentWeight = 1.0;
	F64 cohesionWeight = 1.0;
	F64 pathWeight = 5.0;

	F64 pathSize = 3.0;
	F64 pathRadius = 2.0;

	BoidSystem(int numBoids) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<F64> dis(-2.0, 2.0);

		for (int i = 0; i < numBoids; ++i) {
			// Initialize boids closer to the trefoil knot
			F64 t = (F64)i / numBoids * 2.0 * M_PI;
			F64_V3 knotPoint = Boid::getTrefoilPoint(t, 3.0);

			// Add some random offset from the knot
			F64_V3 offset(dis(gen) * 0.5f, dis(gen) * 0.5, dis(gen) * 0.5);
			F64_V3 pos = knotPoint + offset;

			boids.emplace_back(pos);
		}
	}

	void update(F64 deltaTime) {
		// Calculate forces for each boid
		for (auto& boid : boids) {
			F64_V3 separation = boid.separate(boids);
			F64_V3 alignment = boid.align(boids);
			F64_V3 cohesion = boid.cohesion(boids);
			F64_V3 pathFollow = boid.followPath(pathSize, pathRadius);
			F64_V3 avoidance = boid.avoidObstacles(boids);

			// Apply weighted forces
			boid.applyForce(separation * separationWeight);
			boid.applyForce(alignment * alignmentWeight);
			boid.applyForce(cohesion * cohesionWeight);
			boid.applyForce(pathFollow * pathWeight);
			boid.applyForce(avoidance * avoidanceWeight);
		}

		// Update all boids
		for (auto& boid : boids) {
			boid.update(deltaTime);
		}
	}

	const std::vector<Boid>& getBoids() const {
		return boids;
	}

	// Utility function to get trefoil knot curve points for visualization
	std::vector<F64_V3> getTrefoilCurve(int numPoints = 300, F64 scale = 3.0) {
		std::vector<F64_V3> points;
		for (int i = 0; i < numPoints; ++i) {
			F64 t = (F64)i / numPoints * 2.0 * M_PI;
			points.push_back(Boid::getTrefoilPoint(t, scale));
		}
		return points;
	}
};