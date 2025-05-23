#pragma once

#include "rbpch.h"

#include "Robin/core.h"
#include "Robin/log.h"
#include "Robin/Events/event.h"

namespace Robin
{
	struct window_props
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		window_props(const std::string& title = "Robin Engine",
			unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height)
		{
		}
	};

	class ROBIN_API window
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

		virtual void* get_native_window() const = 0;

		static window* create(const window_props& props = window_props());
	};
}