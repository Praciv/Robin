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

		m_vertex_array.reset(vertex_array::create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,  0.1f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f,   0.8f, 0.8f, 0.3f, 1.0f
		};
		
		std::shared_ptr<vertex_buffer> m_vertex_buffer;
		m_vertex_buffer.reset(vertex_buffer::create(vertices, sizeof(vertices)));
		buffer_layout layout = {
			{ shader_data_type::Float3, "a_position" },
			{ shader_data_type::Float4, "a_colour" }
		};
		m_vertex_buffer->set_layout(layout);
		m_vertex_array->add_vertex_buffer(m_vertex_buffer);

		unsigned int indices[] = {0, 1, 2};
		std::shared_ptr<index_buffer> m_index_buffer;
		m_index_buffer.reset(index_buffer::create(indices, sizeof(indices)));
		m_vertex_array->set_index_buffer(m_index_buffer);

		std::string vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_colour;
		
			out vec3 v_position;
			out vec4 v_colour;

			void main()
			{
				v_position = a_position;
				v_colour = a_colour;
				gl_Position = vec4(a_position, 1.0);
			}
		)";

		std::string fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 frag_colour;
		
			in vec3 v_position;
			in vec4 v_colour;

			void main()
			{
				frag_colour = vec4(v_position * 0.5 + 0.5, 1.0);
				frag_colour = v_colour;
			}
		)";

		m_shader.reset(shader::create(vertex_source, fragment_source));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->bind();
			m_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			m_vertex_array->unbind();

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