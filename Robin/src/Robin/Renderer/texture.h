#pragma once

namespace Robin
{
	class texture
	{
	public:
		virtual const uint32_t get_height() const = 0;
		virtual const uint32_t get_width() const = 0;

		virtual const uint32_t get_id() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;
	};

	class texture_2D : public texture
	{
	public:
		static ref<texture_2D> create();
		static ref<texture_2D> create(const std::string& path);
	};
}