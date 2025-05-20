#version 460 core

out vec4 fragColor;

uniform sampler2D uFG;
uniform sampler2D uBG;

in vec2 vTexCoord;

void main() {
	vec4 fg = texture(uFG, vTexCoord);
	vec4 bg = texture(uBG, vTexCoord);
	fragColor = mix(fg, bg, fg.a);
}