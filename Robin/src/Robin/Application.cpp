#include "rbpch.h"
#include "application.h"

#include "Robin/log.h"

#include <glad/glad.h>

#include "input.h"

namespace Robin 
{

#define BIND_EVENT_FN(x) std::bind(&application::x, this, std::placeholders::_1)
	
	application* application::s_instance = nullptr;

	application::application()
	{
		RB_CORE_ASSERT(!s_instance, "Application already exists")
		s_instance = this;

		m_window = std::unique_ptr<window>(window::create());
		m_window->set_event_callback(BIND_EVENT_FN(on_event));

		m_imgui_layer = new imgui_layer;
		push_overlay(m_imgui_layer);
	}

	application::~application()
	{

	}

	void application::push_layer(layer* layer)
	{
		m_layer_stack.push_layer(layer);
		layer->on_attach();
	}
	
	void application::push_overlay(layer* overlay)
	{
		m_layer_stack.push_layer(overlay);
		overlay->on_attach();
	}

	void application::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<window_close_event>(BIND_EVENT_FN(on_window_close));
		
		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
		{
			(*--it)->on_event(e);
			if (e.handled)
				break;
		}
	}

	void application::run()
	{
		while (m_running)
		{
			static const GLfloat bgd[] = { .8f, .8f, .8f, 1.f };
			glClearBufferfv(GL_COLOR, 0, bgd);
			glClear(GL_COLOR_BUFFER_BIT);

			for (layer* layer : m_layer_stack)
				layer->on_update();

			m_imgui_layer->begin();
			for (layer* layer : m_layer_stack)
				layer->on_imgui_render();
			m_imgui_layer->end();

			m_window->on_update();
		}
	}

	bool application::on_window_close(window_close_event& e)
	{
		m_running = false; 
		return true;
	}
}