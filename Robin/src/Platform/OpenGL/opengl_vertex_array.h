#pragma once

#include "Robin/Renderer/vertex_array.h"

namespace Robin
{
	class opengl_vertex_array : public vertex_array
	{
	public:
		opengl_vertex_array();
		~opengl_vertex_array();

		void bind() const;
		void unbind() const;

		void add_vertex_buffer(const ref<vertex_buffer>& vertex_buffer) override;
		void set_index_buffer(const ref<index_buffer>& index_buffer) override;

		const std::vector<ref<vertex_buffer>>& get_vertex_buffers()  const { return m_vertex_buffers; };
		const ref<index_buffer>& get_index_buffer() const { return m_index_buffer; }

	private:
		std::vector<ref<vertex_buffer>> m_vertex_buffers;
		ref<index_buffer> m_index_buffer;

		uint32_t m_renderer_id = 0;
	};
}

