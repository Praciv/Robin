#include <Robin.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class example_layer : public Robin::layer
{
public:
	example_layer()
		: layer("example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_camera_position(0.f), m_camera_rotation(0.f), m_colour(1.f)
	{
		m_vertex_array.reset(Robin::vertex_array::create());

		float vertices[5 * 4] =
		{
			 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,      0.0f, 1.0f    // top left 
		};


		Robin::ref<Robin::vertex_buffer> m_vertex_buffer;
		m_vertex_buffer.reset(Robin::vertex_buffer::create(vertices, sizeof(vertices)));
		Robin::buffer_layout layout = {
			{ Robin::shader_data_type::Float3, "a_position" },
			{ Robin::shader_data_type::Float2, "a_tex_coord" }
		};
		m_vertex_buffer->set_layout(layout);
		m_vertex_array->add_vertex_buffer(m_vertex_buffer);

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		Robin::ref<Robin::index_buffer> m_index_buffer;
		m_index_buffer.reset(Robin::index_buffer::create(indices, sizeof(indices)));
		m_vertex_array->set_index_buffer(m_index_buffer);

		std::string vertex_source = R"(
			#version 330 core
			
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
		)";

		std::string fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 frag_colour;

			uniform sampler2D u_texture; 
		
			in vec2 v_tex_coord;

			void main()
			{
				frag_colour = texture(u_texture, v_tex_coord);
			}
		)";

		m_shader.reset(Robin::shader::create(vertex_source, fragment_source));
	
		m_texture = Robin::texture_2D::create("assets/textures/first_aid_logo.png");

		m_texture->bind();
		m_shader->set_int("u_texture", 0);
	}

	void on_update(Robin::timestep delta_time) override
	{
		if (Robin::input::is_key_pressed(RB_KEY_D))
			m_camera_position.x -= m_camera_speed * delta_time;
		else if (Robin::input::is_key_pressed(RB_KEY_A))
			m_camera_position.x += m_camera_speed * delta_time;

		if (Robin::input::is_key_pressed(RB_KEY_W))
			m_camera_position.y -= m_camera_speed * delta_time;
		else if (Robin::input::is_key_pressed(RB_KEY_S))
			m_camera_position.y += m_camera_speed * delta_time;


		if (Robin::input::is_key_pressed(RB_KEY_Q))
			m_camera_rotation -= m_camera_rotation_speed * delta_time;
		else if (Robin::input::is_key_pressed(RB_KEY_E))
			m_camera_rotation += m_camera_rotation_speed * delta_time;

		Robin::render_command::set_clear_colour({ 0.1f, 0.1f, 0.1f, 1 });
		Robin::render_command::clear();

		m_camera.set_position(m_camera_position);
		m_camera.set_rotation(m_camera_rotation);

		Robin::renderer::begin_scene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int i = 0; i < 5; i++)
		{
			glm::vec3 pos = glm::vec3(i * 0.11f, 0.f, 0.f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			
			Robin::renderer::submit(m_shader, m_vertex_array, transform);
		}

		Robin::renderer::end_scene();
	}

	void on_event(Robin::event& event) override
	{

	}

	void on_imgui_render()
	{
		ImGui::ColorEdit3("Colour", glm::value_ptr(m_colour));
	}

private:
	Robin::ref<Robin::shader> m_shader;
	Robin::ref<Robin::vertex_array> m_vertex_array;
	Robin::ref<Robin::texture_2D> m_texture; 
	glm::mat4 m_transform;

	glm::vec3 m_colour;

	Robin::othorgraphic_camera m_camera;
	glm::vec3 m_camera_position; 
	float m_camera_rotation;

	float m_camera_speed = 1.0f;
	float m_camera_rotation_speed = 20.0f;
};

class sandbox : public Robin::application
{
public: 
	sandbox()
	{
		push_layer(new example_layer());
	}

	~sandbox()
	{

	}
};

Robin::application* Robin::create_application()
{
	return new sandbox();
}