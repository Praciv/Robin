#pragma once

#include "event.h"

namespace Robin
{
	class ROBIN_API mouse_moved_event : public event
	{
	public:
		mouse_moved_event(float x, float y)
			: m_mouse_x(x), m_mouse_y(y) {}

		inline float get_x() const { return m_mouse_x; }
		inline float get_y() const { return m_mouse_y; }


		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_moved_event: " << get_x() << ", " << get_y();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_moved)
		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	private:
		float m_mouse_x, m_mouse_y;
	};

	class ROBIN_API mouse_scrolled_event : public event
	{
	public:
		mouse_scrolled_event(float x_offset, float y_offset)
			: m_x_offset(x_offset), m_y_offset(y_offset) {}

		inline float get_x_offset() const { return m_x_offset; }
		inline float get_y_offset() const { return m_y_offset; }


		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_scrolled_event: " << get_x_offset() << ", " << get_y_offset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_scrolled)
			EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	private:
		float m_x_offset, m_y_offset;
	};

	class ROBIN_API mouse_button_event : public event
	{
	public:
		inline float get_mouse_button() const { return m_button; }

		EVENT_CLASS_CATEGORY(event_category_mouse | event_category_input)
	protected:
		mouse_button_event(int button)
			: m_button(button) {}

		int m_button;
	};

	class ROBIN_API mouse_button_pressed_event : public mouse_button_event
	{
	public:
		mouse_button_pressed_event(int button)
			: mouse_button_event(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_button_pressed_event: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_button_pressed)
	};

	class ROBIN_API mouse_button_released_event : public mouse_button_event
	{
	public:
		mouse_button_released_event(int button)
			: mouse_button_event(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_button_released_event: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouse_button_released)
	};
}