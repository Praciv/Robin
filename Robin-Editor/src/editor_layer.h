#pragma once

#include "Robin.h"

namespace Robin
{
	class editor_layer : public layer
	{
	public:
		editor_layer();
		~editor_layer();

		void on_attach() override;
		void on_detach() override;
		void on_update(timestep delta_time) override;
		void on_imgui_render() override;
		void on_event(event& event) override;

	private:
		bool on_button_press(mouse_button_pressed_event& e);
		bool on_button_release(mouse_button_released_event& e);
		bool is_cursor_visible();
	private:
		shader_library m_shader_library;

		ref<vertex_array> m_vertex_array;
		ref<texture_2D> m_texture;
		ref<texture_2D> m_transparent_texture;
		ref<texture_2D> m_current_texture;

		ref<vertex_array> m_screen_vertex_array;
		ref<framebuffer> m_framebuffer;
		glm::vec2 m_viewport_size = { 0, 0 };

		glm::mat4 m_transform;
		glm::mat4 m_origin;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_colour;


		float m_scale;

		perspective_camera_controller m_camera_controller;
	};
}