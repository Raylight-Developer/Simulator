#version 450 core

layout(location = 0) in vec2 aPos;

uniform uvec2 uResolution;

uniform vec2  uCenter;
uniform float uZoom;

void main() {
	vec2 ndc = (((aPos + uCenter) * uZoom) / vec2(uResolution)) * 2.0;
	gl_Position = vec4(ndc, 0.0, 1.0);
}