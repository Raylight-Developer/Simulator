#version 460 core

out vec4 fragColor;

uniform vec4  uColor;
uniform float uRadius;
uniform vec2  uPosition;

in vec2 vTexCoord;

void main() {
	float dist = distance(vTexCoord, uPosition);
	if (dist > 1.0) {
		discard;
	}
	fragColor = uColor;
}