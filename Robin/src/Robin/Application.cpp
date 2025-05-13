#include "rbpch.h"
#include "Application.h"

#include "Robin/Events/ApplicationEvent.h"
#include "Robin/Log.h"

namespace Robin 
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		RB_TRACE(e);

		while (true);
	}
}