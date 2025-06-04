#include "rbpch.h"
#include "shader.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_shader.h"


namespace Robin
{
	shader* shader::create(const std::string& file_path)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl: return new opengl_shader(file_path);
		}

		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}

	shader* shader::create(const std::string& vertex_source, const std::string& fragment_source)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none:
			RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl:
			return new opengl_shader(vertex_source, fragment_source);
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}