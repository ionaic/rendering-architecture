#version 330

in vec4 oPosition;
in vec4 oColor;
in vec3 oNormal;
in vec2 oUv;

out vec4 frag_Color;

void main() {
    frag_Color = oColor;
}
