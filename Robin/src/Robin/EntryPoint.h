#pragma once

#ifdef RB_PLATFORM_WINDOWS

extern Robin::Application* Robin::Create_Application();

int main(int argc, char** argv)
{
	auto app = Robin::Create_Application();
	app->Run();
	delete app;
}

#endif