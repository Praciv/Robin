#pragma once

#include "Robin/Renderer/vertex_array.h"

namespace Robin
{
	class opengl_vertex_array : public vertex_array
	{
	public:
		opengl_vertex_array();
		~opengl_vertex_array();

		void bind() const;
		void unbind() const;

	private:
		uint32_t m_renderer_id = 0;
	};
}

