#pragma once

#include "core.h"

namespace Robin {

	class __declspec(dllexport)Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
	};

	// To be defined in the client
	Application* Create_Application();
}

