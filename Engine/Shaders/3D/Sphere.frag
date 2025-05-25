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

void main() {
	vec3 uLightDir = normalize(vec3(1, 1 ,-1));

	vec2 uv = vTexCoord * 2.0 - 1.0; // Convert from [0,1] to [-1,1]
	uv.x *= float(uResolution.x) / float(uResolution.y); // Correct aspect ratio

	vec3 rayOrigin = vec3(0.0, 0.0, 250.0);
	vec3 rayDir = normalize(vec3(uv, -1.0));

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
				float diff = max(dot(normal, normalize(-uLightDir)), 0.0);
				vec3 baseColor = colors[i].rgb;
				finalColor = vec4(baseColor * diff, colors[i].a);
				finalColor = vec4(0,1,0,1);
			}
		}
	}

	fragColor = finalColor;
}