#pragma once
#include "Robin/Renderer/framebuffer.h"

namespace Robin
{
	class opengl_framebuffer : public framebuffer
	{
	public:
		opengl_framebuffer(const framebuffer_specification& specification);
		virtual ~opengl_framebuffer();

		void bind() const override;
		void unbind() const override;

		const framebuffer_specification& get_specicication() const override { return m_specification; };

		const uint32_t get_renderer_id() const override{ return m_renderer_id; }
		const uint32_t get_colour_attachment_renderer_id() const override { return m_colour_attachment; };
	private:
		void invalidate();
	private:
		framebuffer_specification m_specification; 

		uint32_t m_renderer_id; 
		uint32_t m_colour_attachment;
		uint32_t m_depth_attachment;
		uint32_t m_renderbuffer_id;
		ref<texture_2D> m_texture;
	};
}