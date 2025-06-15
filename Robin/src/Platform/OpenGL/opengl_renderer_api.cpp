#include "rbpch.h"
#include "opengl_renderer_api.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Robin
{
	void opengl_renderer_api::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void opengl_renderer_api::set_viewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void opengl_renderer_api::set_clear_colour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void opengl_renderer_api::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void opengl_renderer_api::set_mouse_visibility(bool is_visible)
	{
	}

	void opengl_renderer_api::draw_indexed(const ref<vertex_array>& vertex_array)
	{
		glDrawElements(GL_TRIANGLES, vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
	}
}