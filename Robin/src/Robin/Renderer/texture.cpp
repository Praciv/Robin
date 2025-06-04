#include "rbpch.h"
#include "texture.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_texture.h"

namespace Robin
{
	ref<texture_2D> texture_2D::create(const std::string& path)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl: return std::make_shared<opengl_texture_2D>(path);
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
	}
}