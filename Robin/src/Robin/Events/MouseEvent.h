#pragma once

#include "Event.h"

namespace Robin
{
	class ROBIN_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_mouse_x(x), m_mouse_y(y) {}

		inline float get_x() const { return m_mouse_x; }
		inline float get_y() const { return m_mouse_y; }


		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << get_x() << ", " << get_y();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_moved)
		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	private:
		float m_mouse_x, m_mouse_y;
	};

	class ROBIN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x_offset, float y_offset)
			: m_x_offset(x_offset), m_y_offset(y_offset) {}

		inline float get_x_offset() const { return m_x_offset; }
		inline float get_y_offset() const { return m_y_offset; }


		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_x_offset() << ", " << get_y_offset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_scrolled)
			EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	private:
		float m_x_offset, m_y_offset;
	};

	class ROBIN_API MouseButtonEvent : public Event
	{
	public:
		inline float get_mouse_button() const { return m_button; }

		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class ROBIN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_button_pressed)
	};

	class ROBIN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_button_released)
	};
}