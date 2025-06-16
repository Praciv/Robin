#include "rbpch.h"
#include "opengl_framebuffer.h"

#include "Robin/Core/application.h"

#include <glad/glad.h>

namespace Robin
{
	opengl_framebuffer::opengl_framebuffer(const framebuffer_specification& specification)
		: m_specification(specification)
	{
		invalidate();
	}

	opengl_framebuffer::~opengl_framebuffer()
	{
		glDeleteFramebuffers(1, &m_renderer_id);
	}

	void opengl_framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
	}

	void opengl_framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void opengl_framebuffer::invalidate()
	{
		glCreateFramebuffers(1, &m_renderer_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_colour_attachment);
		glBindTexture(GL_TEXTURE_2D, m_colour_attachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colour_attachment, 0);


		glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_attachment);
		glBindTexture(GL_TEXTURE_2D, m_depth_attachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			RB_CORE_ASSERT(false, "Framebuffer is not complete");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}