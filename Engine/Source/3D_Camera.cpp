#include "3D_Camera.hpp"

void Camera_3D::translate(const F64_V3& offset) {
	F64_V3 forward = glm::normalize(target - position);
	F64_V3 right = glm::normalize(glm::cross(forward, up));
	F64_V3 move = offset.x * right + offset.y * up + offset.z * forward;
	position += move;
	target += move;
}

void Camera_3D::rotate(const F64& pitch, const F64& yaw) {
	F64_V3 forward = glm::normalize(target - position);

	F64 r = glm::length(forward);
	F64 theta = atan2(forward.z, forward.x);
	F64 phi = acos(forward.y / r);

	theta += glm::radians(yaw);
	phi = glm::clamp(phi + glm::radians(pitch), 0.001, glm::pi<F64>() - 0.001);

	forward.x = r * sin(phi) * cos(theta);
	forward.y = r * cos(phi);
	forward.z = r * sin(phi) * sin(theta);

	target = position + forward;
}

void Camera_3D::orbit(const F64& pitch, const F64& yaw, const F64& radius) {
	target = glm::dvec3(0.0);

	F64_V3 offset = position - target;
	F64 r = (radius > 0.0) ? radius : glm::length(offset);

	F64 theta = atan2(offset.z, offset.x);
	F64 phi = acos(offset.y / r);

	theta += glm::radians(yaw);
	phi = glm::clamp(phi + glm::radians(pitch), 0.001, glm::pi<F64>() - 0.001);

	offset.x = r * sin(phi) * cos(theta);
	offset.y = r * cos(phi);
	offset.z = r * sin(phi) * sin(theta);

	position = target + offset;
}

F64_M4 Camera_3D::getViewMatrix() const {
	return glm::lookAt(position, target, up);
}

F64_V3 Camera_3D::getForwardVec() const {
	return glm::normalize(target - position);
}