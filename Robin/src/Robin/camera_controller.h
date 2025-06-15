#pragma once

#include "Robin/Renderer/camera.h"
#include "Robin/Core/timestep.h"

#include "Robin/input.h"
#include "Robin/key_codes.h"

#include "Robin/Events/application_event.h"
#include "Robin/Events/mouse_event.h"

namespace Robin
{
	class orthorgrathic_camera_controller
	{
	public:
		orthorgrathic_camera_controller(float aspect_ratio, bool rotation);

		void on_update(timestep delta_time);
		void on_event(event& e);

		orthorgraphic_camera& get_camera() { return m_camera; }
		const orthorgraphic_camera& get_camera() const { return m_camera; }

	private:
		bool on_mouse_scrolled(mouse_scrolled_event& e);
		bool on_window_resized(window_resize_event& e);
	private:
		float m_aspect_ratio;
		float m_zoom_level = 1.f;
		orthorgraphic_camera m_camera;
		
		bool m_rotation;
		glm::vec3 m_camera_position = glm::vec3(0.f);
		float m_camera_rotation = 0.f;
		float m_camera_translation_speed = 0.2f;
		float m_camera_rotation_speed = 0.5f;
	};

	class perspective_camera_controller
	{
	public:
		perspective_camera_controller(float fov, float width, float height, float near_plane, float far_plane);

		void on_update(timestep delta_time);
		void on_event(event& e);

		perspective_camera& get_camera() { return m_camera; }
		const perspective_camera& get_camera() const { return m_camera; }

		void set_cursor_visibility(bool visibility) { m_is_cursor_visible = visibility; }
		void set_is_first_mouse(bool is_first_mouse) { m_first_mouse = is_first_mouse; }

	private:
		void process_mouse_movement(float x_offset, float y_offset);

		bool on_mouse_scrolled(mouse_scrolled_event& e);
		bool on_window_resized(window_resize_event& e);
	private:
		float m_fov;
		float m_width = 1280.f, m_height = 720.f;
		float m_near_plane = 0.1f, m_far_plane = 100.f;
		perspective_camera m_camera;

		bool m_is_cursor_visible = true;
		float m_last_x = 0.f;
		float m_last_y = 0.f;
		bool m_first_mouse = true;

		glm::vec3 m_camera_position = glm::vec3(0.f, 0.f, 3.f);
		float m_camera_rotation = 0.f;
		float m_camera_translation_speed = 1.f;
		float m_mouse_sensitivity = 0.2f;
	};
}