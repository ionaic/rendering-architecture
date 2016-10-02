vec4 position;
vec4 color;
vec3 normal;
vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = position;
}
