#pragma once

#include "rbpch.h"

#include "Robin/Core/core.h"
#include "Robin/Core/log.h"
#include "Robin/Events/event.h"

namespace Robin
{
	struct window_props
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		window_props(const std::string& title = "Robin Engine",
			uint32_t width = 1280, 
			uint32_t height = 720)
			: title(title), width(width), height(height)
		{
		}
	};

	class window
	{
	public:
		using event_callback_fn = std::function<void(event&)>;

		virtual ~window() {}

		virtual void on_update() = 0;

		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual void set_event_callback(const event_callback_fn& callback) = 0;
		virtual void set_vsync(bool enabled) = 0;
		virtual bool is_vsync() const = 0;

		virtual void set_cursor_visibility(bool enabled) = 0;
		virtual bool get_cursor_visibility() = 0;


		virtual void* get_native_window() const = 0;

		static window* create(const window_props& props = window_props());
	};
}