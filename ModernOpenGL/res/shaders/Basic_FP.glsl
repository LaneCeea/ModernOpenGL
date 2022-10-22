#version 460 core

in vec4 v_out_Color;

out vec4 f_out_Color;

void main() {
    f_out_Color = v_out_Color;
}