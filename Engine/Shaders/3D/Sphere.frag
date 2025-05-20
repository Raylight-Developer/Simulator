#version 460 core

out vec4 fragColor;

uniform mat4 uView;
uniform mat4 uProjection;

uniform vec4  uColor;
uniform float uRadius;
uniform vec3  uPosition;
uniform vec3  uLightDir;
uniform vec3  uCameraPos;

in vec3  vWorldCenter;
in vec2  vFragCoord;
in float vRadius;

void main() {
	float r2 = dot(vQuadCoord, vQuadCoord);
	if (r2 > 1.0) {
		discard; // Outside circle
	}

	// Reconstruct normal from quad position (screen-space unit circle)
	float z = sqrt(1.0 - r2);
	vec3 localNormal = normalize(vec3(vQuadCoord, z)); // Local sphere normal

	// Transform local normal to world space
	// Since billboard is axis-aligned (XY), normal is valid in world space directly

	float diff = max(dot(localNormal, normalize(uLightDir)), 0.0);

	fragColor = uColor * diff;

	vec3 fragPos = vWorldCenter + localNormal * uRadius;
	vec4 clipPos = uProjection * uView * vec4(fragPos, 1.0);
	float ndcDepth = clipPos.z / clipPos.w;        // [-1, 1]
	float depth = ndcDepth * 0.5 + 0.5;             // [0, 1]
	gl_FragDepth = depth;
}