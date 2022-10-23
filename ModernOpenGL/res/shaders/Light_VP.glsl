#version 460 core

layout (location = 0) in vec3 v_in_Position;

uniform mat4 u_Mvp;

void main() {
    gl_Position = u_Mvp * vec4(v_in_Position, 1.0f);
}