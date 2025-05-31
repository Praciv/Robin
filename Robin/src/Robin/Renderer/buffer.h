#pragma once

namespace Robin
{
	class vertex_buffer
	{
	public:
		virtual ~vertex_buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static vertex_buffer* create(float* vertices, uint32_t size);
	};

	class index_buffer
	{
	public:
		virtual ~index_buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static index_buffer* create(uint32_t* indices, uint32_t size);
	};
}