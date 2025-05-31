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
		void unbind()const ;

	private:
		uint32_t m_renderer_id;
	};
}