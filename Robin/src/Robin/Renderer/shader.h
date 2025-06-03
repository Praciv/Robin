#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Robin
{

	class shader
	{
	public:
		virtual ~shader() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_mat4(const std::string& name, const glm::mat4& matrix) const = 0; 

		static shader* create(const std::string& vertex_source, const std::string& fragment_source);
	};
}