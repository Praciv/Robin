#pragma once

#include <string>

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

		static shader* create(const std::string& vertex_source, const std::string& fragment_source);
	};
}