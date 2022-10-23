#version 460 core

out vec4 f_out_Color;

uniform vec4 u_LightColor;

void main() {
    f_out_Color = u_LightColor;
}