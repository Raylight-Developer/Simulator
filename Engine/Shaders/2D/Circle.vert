#version 460 core

layout(location = 0) in vec2 aPos;

uniform uvec2 uResolution;

uniform vec2  uCenter;
uniform float uZoom;

uniform vec2  uPosition;
uniform float uRadius;

out vec2 vTexCoord;

void main() {
	vec2 ndc = ((uCenter * uZoom + ((aPos * uRadius + uPosition) * uZoom)) / vec2(uResolution)) * 2.0;
	vTexCoord = aPos + uPosition;
	gl_Position = vec4(ndc, 0.0, 1.0);
}