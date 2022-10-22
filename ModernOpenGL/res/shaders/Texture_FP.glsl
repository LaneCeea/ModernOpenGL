#version 460 core

in vec4 v_out_Color;
in vec2 v_out_TexCoord;

out vec4 f_out_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
    f_out_Color = texture(u_Texture, v_out_TexCoord) * u_Color * v_out_Color;
}