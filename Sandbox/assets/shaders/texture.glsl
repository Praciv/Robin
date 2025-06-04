#type vertex
#version 450 core
			
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_tex_coord;
		
uniform mat4 u_view_projection_matrix;
uniform mat4 u_model_matrix;

out vec2 v_tex_coord;

void main()
{
	v_tex_coord = a_tex_coord;
	gl_Position = u_view_projection_matrix * u_model_matrix * vec4(a_position, 1.0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#type fragment
#version 450 core
			
layout(location = 0) out vec4 frag_colour;

uniform sampler2D u_texture; 
		
in vec2 v_tex_coord;

void main()
{
	frag_colour = texture(u_texture, v_tex_coord);
}