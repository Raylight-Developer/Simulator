#version 450 core

layout(location = 0) in vec2 aPos;

out vec2 vFragCoord;

uniform uvec2 uResolution;
uniform vec2  uCenter;
uniform float uRadius;

void main() {
	vec2 ndc = ((uCenter + (aPos * uRadius)) / vec2(uResolution)) * 2.0;
	vFragCoord = aPos;
	gl_Position = vec4(ndc, 0.0, 1.0);
}