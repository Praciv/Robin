#pragma once

#include "Robin/Renderer/buffer.h"

namespace Robin
{
	class opengl_vertex_buffer : public vertex_buffer
	{
	public:
		opengl_vertex_buffer(float* vertices, uint32_t size);
		virtual ~opengl_vertex_buffer(); 

		virtual void bind() const;
		virtual void unbind() const;

	private:
		uint32_t m_renderer_id = 0;
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