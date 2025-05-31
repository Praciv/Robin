#include "rbpch.h"
#include "vertex_array.h"

#include "renderer.h"

namespace Robin
{
	vertex_array* vertex_array::create()
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_API::none:
			RB_CORE_ASSERT(false, "renderer API: none not supported");
			break;
		case renderer_API::opengl:
			//return new opengl_vertex_buffer(vertices, size);
			break;
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}