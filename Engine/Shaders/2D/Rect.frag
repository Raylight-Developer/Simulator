#version 450 core

out vec4 o_frag_color;

uniform vec4 u_color;

void main() {
	o_frag_color = u_color;
}