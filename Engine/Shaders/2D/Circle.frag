#version 450 core

out vec4 fragColor;

in vec2 vFragCoord;

uniform vec4  uColor;
uniform vec2  uCenter;
uniform float uRadius;

void main() {
	float dist = distance(vFragCoord, uCenter);
	if (dist > 1.0) {
		discard;
	}
	fragColor = uColor;
}