#pragma once

#include "render_command.h"

namespace Robin
{
	class renderer
	{
	public:
		static void begin_scene();
		static void end_scene();

		static void submit(const std::shared_ptr<vertex_array>& vertex_array);


		inline static renderer_api::api get_renderer_api() { return renderer_api::get_api(); }
	};
}