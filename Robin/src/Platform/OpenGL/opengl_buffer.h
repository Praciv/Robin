#pragma once

#include "Robin/Renderer/buffer.h"

namespace Robin
{
	class opengl_vertex_buffer : public vertex_buffer
	{
	public:
		opengl_vertex_buffer(float* vertices, uint32_t size);
		virtual ~opengl_vertex_buffer(); 

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const buffer_layout& get_layout() const override { return m_layout; };
		virtual void set_layout(const buffer_layout& layout) override { m_layout = layout; };

	private:
		uint32_t m_renderer_id = 0;
		buffer_layout m_layout;
	};


	///////////////////////////////////////////////////////////////////////////////////////
	//// Index buffer /////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	class opengl_index_buffer : public index_buffer
	{
	public:
		opengl_index_buffer(uint32_t* indices, uint32_t size);
		virtual ~opengl_index_buffer();

		virtual void bind() const;
		virtual void unbind() const;

	private:
		uint32_t m_renderer_id = 0;
	};
}