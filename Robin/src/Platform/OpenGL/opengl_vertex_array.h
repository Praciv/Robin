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

		void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer) override;
		void set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer) override;

		const std::vector<std::shared_ptr<vertex_buffer>>& get_vertex_buffers()  const { return m_vertex_buffers; };
		const std::shared_ptr<index_buffer>& get_index_buffer() const { return m_index_buffer; }

	private:
		std::vector<std::shared_ptr<vertex_buffer>> m_vertex_buffers;
		std::shared_ptr<index_buffer> m_index_buffer;

		uint32_t m_renderer_id = 0;
	};
}

