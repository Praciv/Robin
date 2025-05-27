#include "rbpch.h"
#include "opengl_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Robin
{
	opengl_context::opengl_context(GLFWwindow* window_handle)
		: m_window_handle(window_handle)
	{
		RB_CORE_ASSERT(window_handle, "window handle is null");
	}

	void opengl_context::init()
	{
		glfwMakeContextCurrent(m_window_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RB_CORE_ASSERT(status, "Failed to initialise Glad")

		RB_CORE_INFO("OpenGL Info:");
		RB_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		RB_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		RB_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));


	}

	void opengl_context::swap_buffers()
	{
		glfwSwapBuffers(m_window_handle);

	}
}