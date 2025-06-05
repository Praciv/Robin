#pragma once

#include "glm/glm.hpp"

namespace Robin
{
	class othorgraphic_camera
	{
	public:
		othorgraphic_camera(float left, float right, float bottom, float top);

		~othorgraphic_camera();

		const glm::vec3& get_position() const { return m_position; }
		void set_position(glm::vec3& position) { m_position = position; create_view_matrix(); }
		
		const float get_rotation() const { return m_rotation; }
		void set_rotation(float rotation) { m_rotation = rotation; create_view_matrix(); }

		const glm::mat4& get_projection_matrix() { return m_projection_matrix; };
		const glm::mat4& get_view_matrix() { return m_view_matrix; }
		const glm::mat4& get_view_projection_matrix() { return m_view_projection_matrix; }

	private:
		void create_view_matrix();
	private:
		glm::mat4 m_projection_matrix; 
		glm::mat4 m_view_matrix;
		glm::mat4 m_view_projection_matrix;

		glm::vec3 m_position;
		float m_rotation = 0.0f;
	};

	class perspective_camera
	{
	public:
		perspective_camera(float fov, float width, float height, float near_plane, float far_plane);
		~perspective_camera();

		const glm::vec3& get_position() const { return m_position; }
		void set_position(glm::vec3& position) { m_position = position; create_view_matrix(); }

		const glm::vec3& get_camera_front() const { return m_front; }
		void set_camera_front(glm::vec3& front) { m_front = front; create_view_matrix(); }

		const glm::vec3& get_camera_right() const { return m_right; }
		void set_camera_right(glm::vec3& right) { m_right = right; create_view_matrix(); }

		const glm::vec3& get_camera_up() const { return m_up; }
		void set_camera_up(glm::vec3& up) { m_right = up; create_view_matrix(); }

		const glm::mat4& get_projection_matrix() { return m_projection_matrix; };
		const glm::mat4& get_view_matrix() { return m_view_matrix; }
		const glm::mat4& get_view_projection_matrix() { return m_view_projection_matrix; }

		void process_mouse_movement(float x_offset, float y_offset);
	private:
		void create_view_matrix();
	private:
		glm::mat4 m_projection_matrix;
		glm::mat4 m_view_matrix;
		glm::mat4 m_view_projection_matrix;

		glm::vec3 m_position;
		glm::vec3 m_front; 
		glm::vec3 m_up; 
		glm::vec3 m_right;
		glm::vec3 m_world_up;

		float m_yaw;
		float m_pitch;

		float m_mouse_sensitivity;

		float m_fov; 
	};
}

