#pragma once

#include "Robin/Renderer/renderer_api.h"

namespace Robin
{
	class opengl_renderer_api : public renderer_api
	{
		void set_clear_colour(const glm::vec4& colour) override;
		void clear() override;

		void draw_indexed(const std::shared_ptr<vertex_array>& vertex_array) override;
	};
}