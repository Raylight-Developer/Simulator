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

vec3 getRayDirection(vec2 uv) {
	float iCameraFocalLength = 0.05;
	float iCameraSensorWidth = 0.036;

	vec3 projection_center = uCameraPos + iCameraFocalLength * uCameraVector;
	vec3 projection_u = normalize(cross(uCameraVector, vec3(0,1,0))) * iCameraSensorWidth;
	vec3 projection_v = normalize(cross(projection_u, uCameraVector)) * (iCameraSensorWidth / 1.0);
	return normalize(projection_center + (projection_u * uv.x) + (projection_v * uv.y) - uCameraPos);
}

void main() {
	vec3 uLightDir = normalize(vec3(1, 1 ,-1));

	vec2 uv = vTexCoord * 2.0 - 1.0; // Convert from [0,1] to [-1,1]
	uv.x *= float(uResolution.x) / float(uResolution.y); // Correct aspect ratio

	vec3 rayOrigin = uCameraPos;
	vec3 rayDir = getRayDirection(uv);

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