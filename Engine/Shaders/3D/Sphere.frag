#version 460 core

layout(location = 0) out vec4 fragColor;

in vec2 vTexCoord;

layout(std430, binding = 0) buffer Spheres {
	vec4 spheres[];
};
layout(std430, binding = 1) buffer Colors {
	vec4 colors[];
};

uniform uint uCount;
uniform uvec2 uResolution;

uniform vec3 uCameraPos;
uniform vec3 uCameraVector;
uniform mat4 uViewMatrix;

bool intersectSphere(vec3 rayOrigin, vec3 rayDir, vec3 center, float radius, out float t, out vec3 hitNormal) {
	vec3 oc = rayOrigin - center;
	float b = dot(oc, rayDir);
	float c = dot(oc, oc) - radius * radius;
	float h = b * b - c;
	if (h < 0.0) return false;
	h = sqrt(h);
	t = -b - h;
	if (t < 0.0) t = -b + h;
	if (t < 0.0) return false;

	vec3 hitPoint = rayOrigin + t * rayDir;
	hitNormal = normalize(hitPoint - center);
	return true;
}

void getRay(inout vec3 pos, inout vec3 dir, vec2 uv) {
//	float focalLength = 0.025;       // 50mm
//	float sensorWidth = 0.036;      // 36mm (full-frame)
//
//	// Compute aspect ratio and sensor height
//	float aspect = float(uResolution.x) / float(uResolution.y);
//	float sensorHeight = sensorWidth / aspect;
//
//	// Convert uv from [0,1] to sensor space [-0.5*width, +0.5*width]
//	vec3 sensorPos;
//	sensorPos.x = (uv.x - 0.5) * sensorWidth;
//	sensorPos.y = (uv.y - 0.5) * sensorHeight;
//	sensorPos.z = 0.0; // sensor plane at z = 0
//
//	// Focal point is behind sensor at (0, 0, -focalLength)
//	vec3 focalPoint = vec3(0.0, 0.0, -focalLength);
//
//	// Direction from sensor point to focal point (in camera space)
//	vec3 localDir = normalize(focalPoint - sensorPos);
//
//	// Transform sensor position and direction to world space
//	pos = (uViewMatrix * vec4(sensorPos, 1.0)).xyz;
//	dir = normalize((uViewMatrix * vec4(localDir, 0.0)).xyz);

	float iCameraFocalLength = 0.05;
	float iCameraSensorWidth = 0.036;

	uv = vTexCoord * 2.0 - 1.0; // Convert from [0,1] to [-1,1]
	uv.x *= float(uResolution.x) / float(uResolution.y); // Correct aspect ratio

	vec3 projection_center = uCameraPos + iCameraFocalLength * uCameraVector;
	vec3 projection_u = normalize(cross(uCameraVector, vec3(0,1,0))) * iCameraSensorWidth;
	vec3 projection_v = normalize(cross(projection_u, uCameraVector)) * (iCameraSensorWidth / 1.0);
	pos = uCameraPos;
	dir= normalize(projection_center + (projection_u * uv.x) + (projection_v * uv.y) - uCameraPos);
}

void main() {
	vec3 uLightDir = normalize(vec3(1, 1 ,-1));

	vec3 rayOrigin;
	vec3 rayDir;
	getRay(rayOrigin, rayDir, vTexCoord);

	//fragColor = vec4(rayDir, 1);
	//return;

	float minT = 1e9;
	vec4 finalColor = vec4(0);

	for (int i = 0; i < uCount; ++i) {
		vec3 center = spheres[i].xyz;
		float radius = spheres[i].w;

		float t;
		vec3 normal;
		if (intersectSphere(rayOrigin, rayDir, center, radius, t, normal)) {
			if (t < minT) {
				minT = t;
				float diff = max(dot(normal, normalize(-uLightDir)), 0.1);
				vec3 baseColor = colors[i].rgb;
				finalColor = vec4(baseColor * diff, colors[i].a);
			}
		}
	}

	fragColor = finalColor;
}