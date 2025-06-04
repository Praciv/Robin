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

		virtual void add_vertex_buffer(const ref<vertex_buffer>& vertex_buffer) = 0;
		virtual void set_index_buffer(const ref<index_buffer>& index_buffer) = 0;

		virtual const std::vector<ref<vertex_buffer>>& get_vertex_buffers() const = 0;
		virtual const ref<index_buffer>& get_index_buffer() const = 0;

		static vertex_array* create();
	};
}
