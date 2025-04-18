#version 450 core

out vec4 fragColor;

uniform sampler2D uFboTexture;

in vec2 vTexCoord;

void main() {
	fragColor = texture(uFboTexture, vTexCoord);
	//fragColor = vec4(vTexCoord.x,vTexCoord.y,0,1);
}