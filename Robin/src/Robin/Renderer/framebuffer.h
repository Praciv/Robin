#pragma once

#include "Robin/Renderer/texture.h"

namespace Robin
{
	struct framebuffer_specification
	{
		uint32_t width = 0, height = 0;
		uint32_t samples = 1;

		bool swap_chain_target = false;
	};

	class framebuffer
	{
	public:
		virtual ~framebuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const framebuffer_specification& get_specicication() const = 0;

		virtual const uint32_t get_renderer_id() const = 0;
		virtual const uint32_t get_colour_attachment_renderer_id() const = 0;

		static ref<framebuffer> create(const framebuffer_specification& specification);
	};

}