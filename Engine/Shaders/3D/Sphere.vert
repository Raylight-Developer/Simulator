#version 460 core

layout(location = 0) in vec2 aPos;

uniform uvec2 uResolution;

uniform mat4 uView;
uniform mat4 uProjection;

uniform vec3  uPosition;
uniform float uRadius;

out vec3  vWorldCenter;
out vec2  vFragCoord;
out float vRadius;

void main() {
	vec3 worldOffset = vec3(aPos * uRadius, 0.0);
	vec4 worldPos = vec4(uPosition + worldOffset, 1.0);

	gl_Position = uProjection * uView * worldPos;

	vQuadCoord = aPos;
	vWorldCenter = uPosition;
	vRadius = uRadius;;
}