#pragma once

#include "core.h"
#include "Events/event.h"
#include "Robin/Events/application_event.h"

#include "window.h"

namespace Robin 
{
	class __declspec(dllexport)application
	{
	public:
		application();
		virtual ~application();

		void run();

		void on_event(event& e);

	private:
		bool on_window_close(window_close_event& e);

		std::unique_ptr<window> m_window;
		bool m_running = true; 
	};

	// To be defined in the client
	application* create_application();
}

