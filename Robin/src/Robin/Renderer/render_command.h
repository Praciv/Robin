#pragma once

#include "renderer_api.h"

namespace Robin
{
	class render_command
	{
	public:
		inline static void set_clear_colour(const glm::vec4& colour)
		{
			s_renderer_api->set_clear_colour(colour);
		}

		inline static void clear()
		{
			s_renderer_api->clear();
		}

		inline static void draw_indexed(const std::shared_ptr<vertex_array>& vertex_array)
		{
			s_renderer_api->draw_indexed(vertex_array);
		}

	private:
		static renderer_api* s_renderer_api;
	};
}