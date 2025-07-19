#include "rbpch.h"
#include "camera_controller.h"

namespace Robin
{
	orthorgrathic_camera_controller::orthorgrathic_camera_controller(float aspect_ratio, bool rotation)
		: m_camera(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level), m_rotation(rotation)
	{
	}
	void orthorgrathic_camera_controller::on_update(timestep delta_time)
	{
		if (input::is_key_pressed(RB_KEY_D))
			m_camera_position.x += m_camera_translation_speed * delta_time;
		else if (input::is_key_pressed(RB_KEY_A))
			m_camera_position.x -= m_camera_translation_speed * delta_time;

		if (input::is_key_pressed(RB_KEY_W))
			m_camera_position.y += m_camera_translation_speed * delta_time;
		else if (input::is_key_pressed(RB_KEY_S))
			m_camera_position.y -= m_camera_translation_speed * delta_time;

		if (m_rotation)
		{
			if (input::is_key_pressed(RB_KEY_Q))
				m_camera_rotation -= m_camera_rotation_speed * delta_time;
			else if (input::is_key_pressed(RB_KEY_E))
				m_camera_rotation += m_camera_rotation_speed * delta_time;

			m_camera.set_rotation(m_camera_rotation);
		}
		m_camera.set_position(m_camera_position);

	}
	void orthorgrathic_camera_controller::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<mouse_scrolled_event>(RB_BIND_EVENT_FN(orthorgrathic_camera_controller::on_mouse_scrolled));
		dispatcher.dispatch<window_resize_event>(RB_BIND_EVENT_FN(orthorgrathic_camera_controller::on_window_resized));

	}
	bool orthorgrathic_camera_controller::on_mouse_scrolled(mouse_scrolled_event& e)
	{
		m_zoom_level -= e.get_y_offset() * 0.25f;
		m_zoom_level = std::max(m_zoom_level, 0.25f);
		m_camera.set_projection(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);
		return false;
	}
	bool orthorgrathic_camera_controller::on_window_resized(window_resize_event& e)
	{
		m_aspect_ratio = (float)e.get_width() / (float)e.get_height();
		m_camera.set_projection(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);
		return false;
	}

	perspective_camera_controller::perspective_camera_controller(float fov, float width, float height, float near_plane, float far_plane)
		: m_camera(fov, width, height, near_plane, far_plane), m_fov(fov), m_width(width), m_height(height), m_near_plane(near_plane), m_far_plane(far_plane)
	{

	}
	void perspective_camera_controller::on_update(timestep delta_time)
	{
		if (input::is_key_pressed(RB_KEY_D))
			m_camera_position += m_camera.get_camera_right() * (m_camera_translation_speed * delta_time);
		else if (input::is_key_pressed(RB_KEY_A))
			m_camera_position -= m_camera.get_camera_right() * (m_camera_translation_speed * delta_time);

		if (input::is_key_pressed(RB_KEY_W))
			m_camera_position += m_camera.get_camera_front() * (m_camera_translation_speed * delta_time);
		else if (input::is_key_pressed(RB_KEY_S))
			m_camera_position -= m_camera.get_camera_front() * (m_camera_translation_speed * delta_time);

		if (input::is_key_pressed(RB_KEY_Q))
			m_camera_position -= m_camera.get_camera_up() * (m_camera_translation_speed * delta_time);
		else if (input::is_key_pressed(RB_KEY_E))
			m_camera_position += m_camera.get_camera_up() * (m_camera_translation_speed * delta_time);

		if (!m_is_cursor_visible)
		{
			auto [x_position, y_position] = input::get_mouse_position();

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

		m_camera.set_position(m_camera_position);
	}
	void perspective_camera_controller::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<mouse_scrolled_event>(RB_BIND_EVENT_FN(perspective_camera_controller::on_mouse_scrolled));
		dispatcher.dispatch<window_resize_event>(RB_BIND_EVENT_FN(perspective_camera_controller::on_window_resized));
	}

	void perspective_camera_controller::on_resize(float width, float height)
	{
		m_width = width;
		m_height = height;

		m_camera.set_projection(m_fov, m_width, m_height, m_near_plane, m_far_plane);
	}


	void perspective_camera_controller::process_mouse_movement(float x_offset, float y_offset)
	{
		x_offset *= m_mouse_sensitivity;
		y_offset *= m_mouse_sensitivity;

		auto yaw = m_camera.get_yaw();
		auto pitch = m_camera.get_pitch();

		m_camera.set_yaw(yaw + x_offset);
		m_camera.set_pitch(pitch + y_offset);

		if (m_camera.get_pitch() > 89.0f)
			m_camera.set_pitch(89.0f);
		if (m_camera.get_pitch() < -89.0f)
			m_camera.set_pitch(-89.0f);
	}

	bool perspective_camera_controller::on_mouse_scrolled(mouse_scrolled_event& e)
	{
		m_fov -= e.get_y_offset();
		m_camera.set_projection(m_fov, m_width, m_height, m_near_plane, m_far_plane);
		return false;
	}
	bool perspective_camera_controller::on_window_resized(window_resize_event& e)
	{
		on_resize((float)e.get_width(), (float)e.get_height());
		return false;
	}
}
