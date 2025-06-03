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
}

