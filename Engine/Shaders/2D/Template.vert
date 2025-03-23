#version 450 core

layout(location = 0) in vec2 aPos;

uniform uvec2 uResolution;

void main() {
	vec2 ndc = (aPos / vec2(uResolution)) * 2.0;
	gl_Position = vec4(ndc, 0.0, 1.0);
}