#pragma once

#include "Robin/Renderer/graphics_context.h"

struct GLFWwindow;

namespace Robin
{
	class opengl_context : public graphics_context
	{
	public:
		opengl_context(GLFWwindow* window_handle);

		void init() override;
		void swap_buffers() override;

	private:
		GLFWwindow* m_window_handle;
	};
}
