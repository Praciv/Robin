#include "rbpch.h"
#include "renderer.h"

namespace Robin
{
	renderer::scene_data* renderer::m_scene_data = new renderer::scene_data;

	void renderer::init()
	{
		render_command::init();
	}

	void renderer::begin_scene(perspective_camera_controller& camera)
	{
		auto perspective_camera = camera.get_camera();
		m_scene_data->view_projection_matrix = perspective_camera.get_view_projection_matrix();
	}
	void renderer::end_scene()
	{

	}

	void renderer::submit_scene(const ref<shader>& shader, const ref<vertex_array>& vertex_array)
	{
		shader->bind();
		vertex_array->bind();
	}

	void renderer::submit(const ref<shader>& shader, const ref<vertex_array>& vertex_array, const glm::mat4& transform)
	{
		shader->bind();
		shader->set_mat4("u_view_projection_matrix", m_scene_data->view_projection_matrix);
		shader->set_mat4("u_model_matrix", transform);
		vertex_array->bind();
		render_command::draw_indexed(vertex_array);
	}
}