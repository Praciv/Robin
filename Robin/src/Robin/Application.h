#pragma once

#include "core.h"

#include "window.h"
#include "Robin/layer_stack.h"
#include "Events/event.h"
#include "Robin/Events/application_event.h"

namespace Robin 
{
	class ROBIN_API application
	{
	public:
		application();
		virtual ~application();

		void run();

		void on_event(event& e);

		void push_layer(layer* layer);
		void push_overlay(layer* overlay);

		inline static application& get() { return *s_instance; }
		inline window& get_window() { return *m_window; }
	private:
		bool on_window_close(window_close_event& e);

		std::unique_ptr<window> m_window;
		bool m_running = true; 
		layer_stack m_layer_stack; 
	private:
		static application* s_instance;
	};

	// To be defined in the client
	application* create_application();
}

