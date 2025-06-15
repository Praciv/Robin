#type vertex
#version 330 core

layout(location 0) in vec2 a_pos; 
layout(location 1) in vec2 a_tex_coords;

out vec2 v_tex_coords; 

void main()
{
	gl_Position = vec4(a_pos.x, a_pos.y, 0.0, 1.0);
	v_tex_coords = a_tex_coords;
}

#type fragment
#version 330 core
layout(location 0) out vec4 frag_colour

in vec2 v_tex_coords;

uniform sampler2D u_screen_texture;

void main()
{
	frag_colour = texture(u_screen_texture, v_tex_coords);
}