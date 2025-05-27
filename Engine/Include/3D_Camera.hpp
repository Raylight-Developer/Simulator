#pragma once

#include "KL.hpp"

struct Camera_3D {
	F64_V3 position = {0.0, 0.0, 10.0};
	F64_V3 target   = {0.0, 0.0, 0.0};
	F64_V3 up       = {0.0, 1.0, 0.0};

	void translate(const F64_V3& offset);
	void rotate(const F64& pitch, const F64& yaw);
	void orbit(const F64& pitch, const F64& yaw, const F64& radius = -1.0);

	F64_M4 getViewMatrix() const;
	F64_V3 getForwardVec() const;
};