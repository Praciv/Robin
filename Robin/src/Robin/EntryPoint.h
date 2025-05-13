#pragma once

#ifdef RB_PLATFORM_WINDOWS

extern Robin::Application* Robin::create_application();

int main(int argc, char** argv)
{
	Robin::Log::init();
	RB_CORE_WARN("initialized log!");
	int a = 5;
	RB_INFO("Hello var={0}", a);


	auto app = Robin::create_application();
	app->run();
	delete app;
}

#endif