#pragma once

#include "core.h"

#include "window.h"
#include "Robin/layer_stack.h"
#include "Events/event.h"
#include "Robin/Events/application_event.h"

#include "Robin/ImGui/imgui_layer.h"

#include "Robin/Core/timestep.h"

namespace Robin 
{
	class application
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

		void close();
	private:
		bool on_window_close(window_close_event& e);
	private:
		scope<window> m_window;
		imgui_layer* m_imgui_layer;
		bool m_running = true; 
		layer_stack m_layer_stack; 

		timestep m_last_frame_time; 
	private:
		static application* s_instance;
	};

	// To be defined in the client
	application* create_application();
}

