#pragma once

#include <memory>
#include "Robin/Renderer/buffer.h"

namespace Robin
{
	class vertex_array
	{
	public:
		virtual ~vertex_array() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer) = 0;
		virtual void set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer) = 0;

		virtual const std::vector<std::shared_ptr<vertex_buffer>>& get_vertex_buffers() const = 0;
		virtual const std::shared_ptr<index_buffer>& get_index_buffer() const = 0;

		static vertex_array* create();
	};
}
