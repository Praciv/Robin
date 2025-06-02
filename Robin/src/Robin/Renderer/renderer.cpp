#include "rbpch.h"
#include "renderer.h"

namespace Robin
{
	void renderer::begin_scene()
	{

	}
	void renderer::end_scene()
	{

	}
	void renderer::submit(const std::shared_ptr<vertex_array>& vertex_array)
	{
		vertex_array->bind();
		render_command::draw_indexed(vertex_array);
	}
}