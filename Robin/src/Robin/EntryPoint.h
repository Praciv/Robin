#pragma once

#ifdef RB_PLATFORM_WINDOWS

extern Robin::Application* Robin::create_application();

int main(int argc, char** argv)
{
	Robin::Log::init();

	auto app = Robin::create_application();
	app->run();
	delete app;
}

#endif