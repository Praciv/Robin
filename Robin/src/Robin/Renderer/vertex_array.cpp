#include "rbpch.h"
#include "vertex_array.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_vertex_array.h"

namespace Robin
{
	vertex_array* vertex_array::create()
	{
		switch (renderer::get_renderer_api())
		{
			case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported"); 
			case renderer_api::api::opengl: return new opengl_vertex_array();
		}

		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}