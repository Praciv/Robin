#include "rbpch.h"
#include "buffer.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_buffer.h"


namespace Robin
{
	vertex_buffer* vertex_buffer::create(float* vertices, uint32_t size)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: 
			RB_CORE_ASSERT(false, "renderer API: none not supported");
			break;
		case renderer_api::api::opengl:
			return new opengl_vertex_buffer(vertices, size);
			break;
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
	
	index_buffer* index_buffer::create(uint32_t* indices, uint32_t size)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none:
			RB_CORE_ASSERT(false, "renderer API: none not supported");
			break;
		case renderer_api::api::opengl:
			return new opengl_index_buffer(indices, size);
			break;
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}