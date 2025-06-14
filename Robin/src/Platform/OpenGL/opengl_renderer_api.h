#pragma once

#include "Robin/Renderer/renderer_api.h"

namespace Robin
{
	class opengl_renderer_api : public renderer_api
	{
		void init() override;

		void set_viewport(int x, int y, int width, int height) override;

		void set_clear_colour(const glm::vec4& colour) override;
		void clear() override;

		void set_mouse_visibility(bool is_visible) override;

		void draw_indexed(const ref<vertex_array>& vertex_array) override;
	};
}