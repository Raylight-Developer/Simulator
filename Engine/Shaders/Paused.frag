#version 460 core

out vec4 fragColor;

uniform sampler2D uFbt;

in vec2 vTexCoord;

void main() {
	fragColor = texture(uFbt, vTexCoord);
}