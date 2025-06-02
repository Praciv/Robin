#pragma once

#include <glm/glm.hpp>

#include "vertex_array.h"

namespace Robin
{
	class renderer_api
	{
	public:
		enum class api
		{
			none = 0, opengl = 1
		};

	public:
		virtual void set_clear_colour(const glm::vec4& colour) = 0;
		virtual void clear() = 0;

		virtual void draw_indexed(const std::shared_ptr<vertex_array>& vertex_array) = 0;

		inline static api get_api() { return s_api; }

	private:
		static api s_api;
	};
}