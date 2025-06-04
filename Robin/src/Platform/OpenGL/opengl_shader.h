#pragma once

#include "Robin/Renderer/shader.h"

namespace Robin
{
	class opengl_shader : public shader
	{
	public: 
		opengl_shader(const std::string& vertex_source, const std::string& fragment_source);
		~opengl_shader();

		void bind() const;
		void unbind()const;

		void set_int(const std::string& name, const int value) const;
		void set_float3(const std::string& name, const glm::vec3& vector) const;
		void set_float4(const std::string& name, const glm::vec4& vector) const;
		void set_mat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		uint32_t m_renderer_id;
	};
}