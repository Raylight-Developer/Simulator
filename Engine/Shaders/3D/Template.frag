#version 450 core

out vec4 fragColor;

in vec3 vfragPos;
in vec3 vfragNormal;

uniform vec4 uColor;

void main() {
	fragColor = uColor;
}