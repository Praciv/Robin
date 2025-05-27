#pragma once

#include <string>

namespace Robin
{
	class shader
	{
	public: 
		shader(const std::string& vertex_source, const std::string& fragment_source);
		~shader();

		void bind() const;
		void unbind() const ;

	private:
		uint32_t m_renderer_id;
	};
}