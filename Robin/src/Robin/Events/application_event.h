#pragma once

#include "event.h"

namespace Robin
{
	class ROBIN_API window_resize_event : public event
	{
	public:
		window_resize_event(float width, float height)
			: m_width(width), m_height(height) {}

		inline unsigned int get_width() const { return m_width; }
		inline unsigned int get_height() const { return m_height; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "window_resize_event: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(window_resize)
		EVENT_CLASS_CATEGORY(event_category_application)
	private:
		unsigned int m_width, m_height;
	};

	class ROBIN_API window_close_event : public event
	{
	public: 
		window_close_event() {}

		EVENT_CLASS_TYPE(window_close)
		EVENT_CLASS_CATEGORY(event_category_application)
	};

	class ROBIN_API app_tick_event : public event
	{
	public:
		app_tick_event() {}

		EVENT_CLASS_TYPE(app_tick)
		EVENT_CLASS_CATEGORY(event_category_application)
	};

	class ROBIN_API app_update_event : public event
	{
	public:
		app_update_event() {}

		EVENT_CLASS_TYPE(app_update)
		EVENT_CLASS_CATEGORY(event_category_application)
	};

	class ROBIN_API app_render_event : public event
	{
	public:
		app_render_event() {}

		EVENT_CLASS_TYPE(app_render)
		EVENT_CLASS_CATEGORY(event_category_application)
	};
}