#include "rbpch.h"
#include "shader.h"

#include "renderer.h"

#include "Platform/OpenGL/opengl_shader.h"


namespace Robin
{
	ref<shader> shader::create(const std::string& file_path)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl: return std::make_shared<opengl_shader>(file_path);
		}

		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}

	ref<shader> shader::create(const std::string& name, const std::string& vertex_source, const std::string& fragment_source)
	{
		switch (renderer::get_renderer_api())
		{
		case renderer_api::api::none: RB_CORE_ASSERT(false, "renderer API: none not supported");
		case renderer_api::api::opengl: return std::make_shared<opengl_shader>(vertex_source, fragment_source);
		}


		RB_CORE_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}

	void shader_library::add(const std::string& name, const ref<shader>& shader)
	{
		RB_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already exists");
		m_shaders[name] = shader;
	}

	void shader_library::add(const ref<shader>& shader)
	{
		auto& name = shader->get_name();
		RB_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already exists");
		add(name, shader);
	}
	ref<shader> shader_library::load(const std::string& file_path)
	{
		auto shader = shader::create(file_path);
		add(shader);
		return shader;
	}
	ref<shader> shader_library::load(const std::string& name, const std::string& file_path)
	{
		auto shader = shader::create(file_path);
		add(name, shader);
		return shader;
	}
	ref<shader> shader_library::get(const std::string& name)
	{
		RB_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader not found");
		return m_shaders[name];
	}
}