#include "rbpch.h"
#include "opengl_texture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Robin
{
	opengl_texture_2D::opengl_texture_2D(const std::string& path)
		:	m_path(path)
	{
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		RB_CORE_ASSERT(data, "Failed to load image!");
		m_width = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);

		GLenum internal_format = 0, data_format = 0;
		
		if (nrChannels == 3)
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
		}

		RB_CORE_ASSERT(internal_format & data_format, "Formats not set");

		glTextureStorage2D(m_renderer_id, 1, internal_format, m_width, m_height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	opengl_texture_2D::~opengl_texture_2D()
	{
		glDeleteTextures(1, &m_renderer_id);
	}

	void opengl_texture_2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_renderer_id);
	}
}