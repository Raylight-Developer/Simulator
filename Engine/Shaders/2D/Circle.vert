#version 450 core

layout(location = 0) in vec2 aPos;

uniform uvec2 uResolution;

uniform vec2  uCenter;
uniform float uZoom;

uniform vec2  uPosition;
uniform float uRadius;

out vec2 vFragCoord;

void main() {
	vec2 ndc = ((uPosition + uCenter * uZoom + (aPos * uZoom * uRadius)) / vec2(uResolution)) * 2.0;
	vFragCoord = aPos;
	gl_Position = vec4(ndc, 0.0, 1.0);
}