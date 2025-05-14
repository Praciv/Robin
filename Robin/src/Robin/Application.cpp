#include "rbpch.h"
#include "application.h"

#include "Robin/log.h"

namespace Robin 
{

#define BIND_EVENT_FN(x) std::bind(&application::x, this, std::placeholders::_1)
	
	application::application()
	{
		m_window = std::unique_ptr<window>(window::create());
		m_window->set_event_callback(BIND_EVENT_FN(on_event));
	}

	application::~application()
	{

	}

	void application::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<window_close_event>(BIND_EVENT_FN(on_window_close));
		
		RB_CORE_TRACE("{0}", e);
	}

	void application::run()
	{
		while (m_running)
		{
			m_window->on_update();
		}
	}

	bool application::on_window_close(window_close_event& e)
	{
		m_running = false; 
		return true;
	}
}