#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Robin
{

	class shader
	{
	public:
		virtual ~shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual void set_int(const std::string& name, const int value) const = 0;
		virtual void set_float3(const std::string& name, const glm::vec3& vector) const = 0;
		virtual void set_float4(const std::string& name, const glm::vec4& vector) const = 0;
		virtual void set_mat4(const std::string& name, const glm::mat4& matrix) const = 0; 

		virtual const std::string& get_name() const = 0;

		static ref<shader> create(const std::string& file_path);
		static ref<shader> create(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
	};

	class shader_library
	{
	public:
		void add(const std::string&name, const ref<shader>& shader);
		void add(const ref<shader>& shader);
		ref<shader> load(const std::string& file_path);
		ref<shader> load(const std::string& name, const std::string& file_path);


		ref<shader> get(const std::string& name);
	private:
		std::unordered_map<std::string, ref<shader>> m_shaders; 
	};
}