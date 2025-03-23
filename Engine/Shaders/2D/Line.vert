#version 450 core

layout (location = 0) in vec2 a_pos;

uniform uvec2 u_resolution;

void main() {
	vec2 ndc = (a_pos / vec2(u_resolution)) * 2.0;

	ndc.y = -ndc.y;
	gl_Position = vec4(ndc, 0.0, 1.0);
}