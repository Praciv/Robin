#pragma once

#include "Robin/window.h"
#include "Robin/renderer/graphics_context.h"

#include <GLFW/glfw3.h>

namespace Robin
{
	class windows_window : public window
	{
	public:
		windows_window(const window_props& props);
		virtual ~windows_window();

		void on_update() override;

		inline unsigned int get_width() const override { return m_data.width; }
		inline unsigned int get_height() const override { return m_data.height; }

		inline void set_event_callback(const event_callback_fn& callback) override { m_data.event_callback = callback; };
		void set_vsync(bool enabled) override;
		bool is_vsync() const override;

		void set_cursor_visibility(bool enabled) override;
		bool get_cursor_visibility() override;


		inline virtual void* get_native_window() const { return m_window; }
	private:
		virtual void init(const window_props& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_window; 
		graphics_context* m_context;

		struct window_data
		{
			std::string title;
			unsigned int width = 0, height = 0;
			bool vsync = 0;

			event_callback_fn event_callback;
		};

		window_data m_data; 
	};

}