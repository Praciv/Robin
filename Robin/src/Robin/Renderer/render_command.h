#pragma once

#include "renderer_api.h"

namespace Robin
{
	class render_command
	{
	public:
		inline static void init()
		{
			s_renderer_api->init();
		}

		inline static void set_viewport(int x, int y, int width, int height)
		{
			s_renderer_api->set_viewport(x, y, width, height);
		}


		inline static void set_clear_colour(const glm::vec4& colour)
		{
			s_renderer_api->set_clear_colour(colour);
		}

		inline static void clear()
		{
			s_renderer_api->clear();
		}

		inline static void set_mouse_visibility(bool is_visible)
		{
			s_renderer_api->set_mouse_visibility(is_visible);
		}

		inline static void draw_indexed(const ref<vertex_array>& vertex_array)
		{
			s_renderer_api->draw_indexed(vertex_array);
		}

	private:
		static renderer_api* s_renderer_api;
	};
}