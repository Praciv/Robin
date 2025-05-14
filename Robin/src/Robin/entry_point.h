#pragma once

#ifdef RB_PLATFORM_WINDOWS

extern Robin::application* Robin::create_application();

int main(int argc, char** argv)
{
	Robin::log::init();

	auto app = Robin::create_application();
	app->run();
	delete app;
}

#endif