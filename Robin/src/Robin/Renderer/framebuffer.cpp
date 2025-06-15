#include "rbpch.h"
#include "framebuffer.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_framebuffer.h"

namespace Robin
{
	ref<framebuffer> framebuffer::create(const framebuffer_specification& specification)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl: return std::make_shared<opengl_framebuffer>(specification);
		}

		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}