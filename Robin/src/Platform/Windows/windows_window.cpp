#include "rbpch.h"
#include "windows_window.h"

#include "Robin/Events/application_event.h"
#include "Robin/Events/key_event.h"
#include "Robin/Events/mouse_event.h"

#include "platform/OpenGL/opengl_context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Robin
{
	static bool s_GLFW_intitialised = false;

	static void GLFW_error_callback(int error, const char* description)
	{
		RB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	
	window* window::create(const window_props& props)
	{
		return new windows_window(props);
	}

	windows_window::windows_window(const window_props& props)
	{
		init(props);
	}

	windows_window::~windows_window()
	{
		shutdown();
	}

	void windows_window::init(const window_props& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		RB_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFW_intitialised)
		{
			// TODO: glfwTerminate on system shudown 
			int success = glfwInit();
			RB_CORE_ASSERT(success, "could not initialise GLFW");

			glfwSetErrorCallback(GLFW_error_callback);

			s_GLFW_intitialised = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);

		m_context = new opengl_context(m_window);
		m_context->init();
		
		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);

		// set GLFW callbacks 
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) 
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height; 

			window_resize_event event(width, height);
			data.event_callback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			window_close_event event;
			data.event_callback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action , int mods)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					key_pressed_event event(key, 0);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					key_released_event event(key);
					data.event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					key_pressed_event event(key, 1);
					data.event_callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key_code)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			key_typed_event event(key_code);
			data.event_callback(event);
		});


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					mouse_button_pressed_event event(button);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					mouse_button_released_event event(button);
					data.event_callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			mouse_scrolled_event event((float)x_offset, (float)y_offset);
			data.event_callback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			mouse_moved_event event((float)x_pos, (float)y_pos);
			data.event_callback(event);
		});
	}

	void windows_window::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void windows_window::on_update()
	{
		glfwPollEvents();
		m_context->swap_buffers();
	}

	void windows_window::set_vsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}

	bool windows_window::is_vsync() const
	{
		return m_data.vsync;
	}

	void windows_window::set_cursor_visibility(bool enabled)
	{
		if (enabled)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	bool windows_window::get_cursor_visibility()
	{
		if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
			return true;
		else
			return false; 
	}
}