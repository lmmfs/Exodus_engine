#version 330 core
in vec3 in_Position;

uniform mat4 lightSpaceMatrix = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main() {
    gl_Position = lightSpaceMatrix * model * vec4(in_Position, 1.0);
} 