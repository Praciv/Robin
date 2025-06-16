#include "editor_layer.h"
#include <Robin.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Robin
{
	editor_layer::editor_layer()
		: layer("example"), m_camera_controller(45.f, 1280.f, 720.f, 0.1f, 100.f), m_colour(1.f), m_position(0.f), m_origin(1.f), m_scale(0.5f), m_rotation(0.f), m_transform(1.f)
	{
	}

	editor_layer::~editor_layer()
	{
	}

	void editor_layer::on_attach()
	{
		m_vertex_array.reset(vertex_array::create());

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

		ref<vertex_buffer> m_vertex_buffer;
		m_vertex_buffer.reset(vertex_buffer::create(vertices, sizeof(vertices)));
		buffer_layout layout = {
			{ shader_data_type::Float3, "a_position" },
			{ shader_data_type::Float2, "a_tex_coord" }
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

		ref<index_buffer> m_index_buffer;
		m_index_buffer.reset(index_buffer::create(indices, sizeof(indices)));
		m_vertex_array->set_index_buffer(m_index_buffer);

		auto shader = shader::create("assets/shaders/texture.glsl");
		m_shader_library.add(shader);

		m_texture = texture_2D::create("assets/textures/first_aid_logo.png");
		m_current_texture = m_texture;
		shader->bind();
		shader->set_int("u_texture", 0);

		framebuffer_specification framebuffer_spec;
		framebuffer_spec.width = 1280;
		framebuffer_spec.height = 720;
		m_framebuffer = framebuffer::create(framebuffer_spec);
	}

	void editor_layer::on_detach()
	{

	}

	void editor_layer::on_update(timestep delta_time)
	{
		m_camera_controller.on_update(delta_time);

		m_framebuffer->bind();
		render_command::set_viewport(0, 0, 1280, 720);
		render_command::set_clear_colour({ 0.1f, 0.1f, 0.1f, 1.f });
		render_command::clear();

		renderer::begin_scene(m_camera_controller);

		auto shader = m_shader_library.get("texture");

		m_current_texture->bind();
		m_transform = glm::translate(m_origin, m_position);
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.f, 0.f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.f, 0.f));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.f, 1.f));
		m_transform = glm::scale(m_transform, glm::vec3(m_scale));

		renderer::submit(shader, m_vertex_array, m_transform);
		m_framebuffer->unbind();

		renderer::end_scene();
	}

	void editor_layer::on_imgui_render()
	{
		static bool docking_enabled = true;

		if (docking_enabled)
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

					if (ImGui::MenuItem("Exit")) application::get().close();

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::End();
		}

		ImGui::Begin("Scene Info");
		auto camera = m_camera_controller.get_camera();

		ImGui::InputFloat3("Transform", glm::value_ptr(m_position));
		ImGui::InputFloat3("Rotation", glm::value_ptr(m_rotation));
		ImGui::SliderFloat("Scale", &m_scale, 0.0f, 1.0f);
		ImGui::SliderFloat("camera z pos", &camera.get_position().z, -5.0f, 5.0f);

		ImGui::End();

		ImGui::Begin("Statistics");

		const auto& samples = timer_manager::get_instance()->get_sample_data();

		float total_frame_time = 0;

		for (auto sample : samples)
		{
			if (sample.name == "Robin::application::run")
			{
				total_frame_time = sample.duration_ms;
			}
		}

		if(total_frame_time != 0)
			ImGui::Text("Frame Time: %.2f ms (%.1f FPS)", 1000.f / total_frame_time, total_frame_time);

		ImGui::End();


		ImGui::Begin("Viewport");

		auto texture = m_framebuffer->get_colour_attachment_renderer_id();
		ImGui::Image((void*)texture, ImGui::GetContentRegionAvail(), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
	}

	void editor_layer::on_event(event& e)
	{
		m_camera_controller.on_event(e);

		event_dispatcher dispatcher(e);
		dispatcher.dispatch<mouse_button_pressed_event>(RB_BIND_EVENT_FN(editor_layer::on_button_press));
		dispatcher.dispatch<mouse_button_released_event>(RB_BIND_EVENT_FN(editor_layer::on_button_release));
	}

	bool editor_layer::on_button_press(mouse_button_pressed_event& e)
	{
		if (e.get_mouse_button() == RB_MOUSE_BUTTON_2)
		{
			application::get().get_window().set_cursor_visibility(false);
			m_camera_controller.set_cursor_visibility(false);
		}

		return false;
	}

	bool editor_layer::on_button_release(mouse_button_released_event& e)
	{
		if (e.get_mouse_button() == RB_MOUSE_BUTTON_2)
		{
			application::get().get_window().set_cursor_visibility(true);
			m_camera_controller.set_cursor_visibility(true);
			m_camera_controller.set_is_first_mouse(true);
		}

		return false;
	}

	bool editor_layer::is_cursor_visible()
	{
		return application::get().get_window().get_cursor_visibility();
	}
}