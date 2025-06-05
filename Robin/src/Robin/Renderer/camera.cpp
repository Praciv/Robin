#include "rbpch.h"
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Robin
{
	othorgraphic_camera::othorgraphic_camera(float left, float right, float bottom, float top)
		: m_projection_matrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_view_matrix(1.f), m_position(0.f)

	{
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	}
	othorgraphic_camera::~othorgraphic_camera()
	{

	}
	void othorgraphic_camera::create_view_matrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_view_matrix = glm::inverse(transform);
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	}

	perspective_camera::perspective_camera(float fov, float width, float height, float near_plane, float far_plane)
		:	m_projection_matrix(glm::perspective(glm::radians(fov), width / height, near_plane, far_plane)), m_view_matrix(1.f), m_position(0.f),
			m_up(glm::vec3(0.f, 1.f, 0.f)), m_world_up(glm::vec3(0.f, 1.f, 0.f)), m_fov(fov), m_yaw(-90.f), m_pitch(0.f), m_mouse_sensitivity(0.075f)
	{
		create_view_matrix();
	}

	perspective_camera::~perspective_camera()
	{

	}

	void perspective_camera::process_mouse_movement(float x_offset, float y_offset)
	{
		x_offset *= m_mouse_sensitivity;
		y_offset *= m_mouse_sensitivity;

		m_yaw += x_offset;
		m_pitch += y_offset;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		create_view_matrix();
	}

	void perspective_camera::create_view_matrix()
	{
		glm::vec3 new_front;
		new_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		new_front.y = sin(glm::radians(m_pitch));
		new_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(new_front);

		m_right = glm::normalize(glm::cross(m_front, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_front));

		m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	}
}