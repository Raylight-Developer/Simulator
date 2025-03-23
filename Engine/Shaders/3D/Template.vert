#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 vfragPos;
out vec3 vfragNormal;

uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;

void main() {
	vfragPos = mat3(uModelMatrix) * aPos;
	vfragNormal = mat3(uModelMatrix) * aNormal;

	gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1.0);
}