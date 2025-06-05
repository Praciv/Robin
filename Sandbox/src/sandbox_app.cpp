#include <Robin.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class example_layer : public Robin::layer
{
public:
	example_layer()
		: layer("example"), m_camera(45.f, (float)Robin::application::get().get_window().get_width(), (float)Robin::application::get().get_window().get_height(), 0.1f, 100.f),
		m_camera_position(glm::vec3(0.f, 0.f, 3.f)), m_camera_rotation(0.f), m_colour(1.f), m_position(0.f), m_origin(1.f), m_scale(0.5f), m_rotation(0.f)
	{
		m_vertex_array.reset(Robin::vertex_array::create());

		float vertices[] = {
			// Positions          // Texture Coords
			// Front face
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left

			// Back face
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right (from perspective of looking at the back)
			 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right

			// Left face
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left (of the left face)
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

			// Right face
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left (of the right face)
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
			 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left

			 // Top face
			 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left (of the top face)
			  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
			  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
			 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left

			 // Bottom face
			 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left (of the bottom face)
			  0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			  0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			 -0.5f, -0.5f,  0.5f,  0.0f, 1.0f  // Top-left
		};

		Robin::ref<Robin::vertex_buffer> m_vertex_buffer;
		m_vertex_buffer.reset(Robin::vertex_buffer::create(vertices, sizeof(vertices)));
		Robin::buffer_layout layout = {
			{ Robin::shader_data_type::Float3, "a_position" },
			{ Robin::shader_data_type::Float2, "a_tex_coord" }
		};
		m_vertex_buffer->set_layout(layout);
		m_vertex_array->add_vertex_buffer(m_vertex_buffer);

		unsigned int indices[] = {
			// Front face
			0, 1, 2,  // First triangle
			2, 3, 0,  // Second triangle

			// Back face (indices 4-7 for vertices)
			4, 5, 6,
			6, 7, 4,

			// Left face (indices 8-11 for vertices)
			8, 9, 10,
			10, 11, 8,

			// Right face (indices 12-15 for vertices)
			12, 13, 14,
			14, 15, 12,

			// Top face (indices 16-19 for vertices)
			16, 17, 18,
			18, 19, 16,

			// Bottom face (indices 20-23 for vertices)
			20, 21, 22,
			22, 23, 20
		};

		Robin::ref<Robin::index_buffer> m_index_buffer;
		m_index_buffer.reset(Robin::index_buffer::create(indices, sizeof(indices)));
		m_vertex_array->set_index_buffer(m_index_buffer);

		auto shader = Robin::shader::create("assets/shaders/texture.glsl");
		m_shader_library.add(shader);

		m_texture = Robin::texture_2D::create("assets/textures/first_aid_logo.png");
		m_transparent_texture = Robin::texture_2D::create("assets/textures/transparent.png");
		m_current_texture = m_texture;
		shader->bind();
		shader->set_int("u_texture", 0);
	}

	void on_update(Robin::timestep delta_time) override
	{
		if (Robin::input::is_key_pressed(RB_KEY_D))
			m_camera_position += m_camera.get_camera_right() * (m_camera_speed * delta_time);
		else if (Robin::input::is_key_pressed(RB_KEY_A))
			m_camera_position -= m_camera.get_camera_right() * (m_camera_speed * delta_time);

		if (Robin::input::is_key_pressed(RB_KEY_W))
			m_camera_position += m_camera.get_camera_front() * (m_camera_speed * delta_time);
		else if (Robin::input::is_key_pressed(RB_KEY_S))
			m_camera_position -= m_camera.get_camera_front() * (m_camera_speed * delta_time);

		if (Robin::input::is_key_pressed(RB_KEY_Q))
			m_camera_position -= m_camera.get_camera_up() * (m_camera_speed * delta_time);
		else if (Robin::input::is_key_pressed(RB_KEY_E))
			m_camera_position += m_camera.get_camera_up() * (m_camera_speed * delta_time);

		if (!is_cursor_visible())
		{
			auto [x_position, y_position] = Robin::input::get_mouse_position();

			if (m_first_mouse)
			{
				m_last_x = x_position;
				m_last_y = y_position;
				m_first_mouse = false;
			}

			float x_offset = x_position - m_last_x;
			float y_offset = m_last_y - y_position;

			m_last_x = x_position;
			m_last_y = y_position;

			m_camera.process_mouse_movement(x_offset, y_offset);
		}

		Robin::render_command::set_clear_colour({ 0.1f, 0.1f, 0.1f, 1 });
		Robin::render_command::clear();

		m_camera.set_position(m_camera_position);

		Robin::renderer::begin_scene(m_camera);

		auto shader = m_shader_library.get("texture");
		
		m_current_texture->bind();
		m_transform = glm::translate(m_origin, m_position);
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.f, 0.f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.f, 0.f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.f, 1.f));
		m_transform = glm::scale(m_transform, glm::vec3(m_scale));
		Robin::renderer::submit(shader, m_vertex_array, m_transform);

		Robin::renderer::end_scene();
	}

	void on_event(Robin::event& e) override
	{
		Robin::event_dispatcher dispatcher(e); 
		dispatcher.dispatch<Robin::mouse_button_pressed_event>(RB_BIND_EVENT_FN(example_layer::on_button_press));
		dispatcher.dispatch<Robin::mouse_button_released_event>(RB_BIND_EVENT_FN(example_layer::on_button_release));
	}

	void on_imgui_render()
	{
		static bool dockspace_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspace_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::Separator();

				if (ImGui::MenuItem("Exit")) Robin::application::get().close();
				
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::Begin("stats");
		
		ImGui::InputFloat3("Transform", glm::value_ptr(m_position));
		ImGui::InputFloat3("Rotation", glm::value_ptr(m_rotation));
		ImGui::SliderFloat("Scale", &m_scale, 0.0f, 1.0f);
		ImGui::SliderFloat("camera z pos", &m_camera_position.z, -5.0f, 5.0f);

		ImGui::End();
	}

	bool on_button_press(Robin::mouse_button_pressed_event& e)
	{
		if (e.get_mouse_button() == RB_MOUSE_BUTTON_2)
		{
			Robin::application::get().get_window().set_cursor_visibility(false);
		}

		return false;
	}

	bool on_button_release(Robin::mouse_button_released_event& e)
	{
		if (e.get_mouse_button() == RB_MOUSE_BUTTON_2)
		{
			Robin::application::get().get_window().set_cursor_visibility(true);
			m_first_mouse = true;
		}

		return false;
	}

	bool is_cursor_visible()
	{
		return Robin::application::get().get_window().get_cursor_visibility();
	}

private:
	Robin::shader_library m_shader_library;

	Robin::ref<Robin::vertex_array> m_vertex_array;
	Robin::ref<Robin::texture_2D> m_texture; 
	Robin::ref<Robin::texture_2D> m_transparent_texture;
	Robin::ref<Robin::texture_2D> m_current_texture;
	
	glm::mat4 m_transform;
	glm::mat4 m_origin;

	glm::vec3 m_position;
	glm::vec3 m_rotation; 
	glm::vec3 m_colour;

	float m_scale; 

	Robin::perspective_camera m_camera;
	glm::vec3 m_camera_position; 
	float m_camera_rotation;

	float m_camera_speed = 1.0f;
	float m_camera_rotation_speed = 20.0f;

	float m_last_x = 0.f;
	float m_last_y = 0.f;
	bool m_first_mouse = true;
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