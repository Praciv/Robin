#pragma once

namespace Robin
{
	class vertex_array
	{
	public:
		virtual ~vertex_array() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static vertex_array* create();
	};
}
