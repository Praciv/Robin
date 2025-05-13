#pragma once

#include "Event.h"

namespace Robin
{
	class ROBIN_API KeyEvent : public Event
	{
	public: 
		inline int get_key_code() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(event_category_keyboard | event_category_input)
	protected:
		KeyEvent(int key_code)
			: m_key_code(key_code) { }

		int m_key_code; 
	};

	class ROBIN_API KeyPressedEvent : public KeyEvent
	{
	public: 
		KeyPressedEvent(int key_code, int repeat_count)
			: KeyEvent(key_code), m_repeat_count(repeat_count) {}

		inline int get_repeat_count() const { return m_repeat_count; }

		std::string to_string() const override
		{
			std::stringstream ss; 
			ss << "KeyPressedEvent: " << m_key_code << " ( " << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(key_pressed)
	private:
		int m_repeat_count; 
	};

	class ROBIN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key_code)
			: KeyEvent(key_code) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(key_pressed)
	};
}