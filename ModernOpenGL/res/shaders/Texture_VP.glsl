#version 460 core

layout (location = 0) in vec3 v_in_Position;
layout (location = 1) in vec4 v_in_Color;
layout (location = 2) in vec2 v_in_TexCoord;

out vec4 v_out_Color;
out vec2 v_out_TexCoord;

uniform mat4 u_Mvp;

void main() {
    gl_Position = u_Mvp * vec4(v_in_Position, 1.0f);
    v_out_Color = v_in_Color;
    v_out_TexCoord = v_in_TexCoord;
}