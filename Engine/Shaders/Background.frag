#version 460 core

uniform float iTime;
uniform int   iFrame;
uniform float iTimeDelta;
uniform vec2  iResolution;

uniform float uZoom;
uniform vec2  uCenter;

in vec2 vTexCoord;

out vec4 fragColor;

void main() {
	vec2 fragCoord = gl_FragCoord.xy;

	fragColor = vec4(1,0,1,1);
}