#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vUV;

out vec2 fUV;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(vPosition, 1.0);
	fUV = vUV;
}