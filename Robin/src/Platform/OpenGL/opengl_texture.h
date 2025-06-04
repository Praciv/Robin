#pragma once

#include "Robin/Renderer/texture.h"

namespace Robin
{
	class opengl_texture_2D : public texture_2D
	{
	public:
		opengl_texture_2D(const std::string& path);
		~opengl_texture_2D();

		uint32_t get_height() const override { return m_height; };
		uint32_t get_width() const override { return m_width; }

		void bind(uint32_t slot = 0) const override;
	private:
		std::string m_path;
		uint32_t m_width, m_height;

		uint32_t m_renderer_id;
	};

}