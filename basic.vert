#version 330

in vec4 position;
in vec4 color;
in vec3 normal;
in vec2 uv;

out vec4 oPosition;
out vec4 oColor;
out vec3 oNormal;
out vec2 oUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = position;
}
