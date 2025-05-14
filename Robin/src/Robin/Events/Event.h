#pragma once
#include "rbpch.h"

#include "Robin/core.h"

namespace Robin
{
	// Events are currently blocking, meaning when an event occurs it 
	// immediately gets dispatched and must be dealt with right then and there.
	// for the future, a better strat might be to buffer events 

	enum class event_type
	{
		none = 0,
		window_close, window_resize, window_focus, window_lost_focus, window_moved,
		app_tick, app_update, app_render,
		key_pressed, key_released, 
		mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled
	};

	enum event_category
	{
		none = 0,
		event_category_application  = BIT(0),
		event_category_input        = BIT(1),
		event_category_keyboard     = BIT(2),
		event_category_mouse        = BIT(3),
		event_category_mouse_button = BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static event_type get_static_type() { return event_type::##type; }\
								virtual event_type get_event_type() const override { return get_static_type(); }\
								virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	class ROBIN_API event
	{
		friend class event_dspatcher; 
	public:
		virtual event_type get_event_type() const = 0; 
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name(); }

		inline bool is_in_category(event_category category)
		{
			return get_category_flags() & category;
		}

		inline void set_handled(bool handled)
		{
			m_handled = handled;
		}

	protected:
		bool m_handled = false; 
	};

	class event_dispatcher
	{
		template<typename T>
		using event_fn = std::function<bool(T&)>;
	public:
		event_dispatcher(event& event)
			: m_event(event)
		{
		}

		template<typename T> 
		bool dispatch(event_fn<T> func)
		{
			if (m_event.get_event_type() == T::get_static_type())
			{
				m_event.set_handled(func(*(T*)&m_event));
				return true; 
			}
			return false; 
		}
	private:
		event& m_event;
	};


	inline std::string format_as(const event& e) {
		return e.to_string();
	}
}