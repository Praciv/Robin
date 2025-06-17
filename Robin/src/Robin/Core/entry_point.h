#pragma once
#include "Robin/Core/core.h"

#ifdef RB_PLATFORM_WINDOWS 

extern Robin::application* Robin::create_application();

int main(int argc, char** argv)
{
	Robin::log::init();

	RB_PROFILE_BEGIN_SESSION("startup", "robin_profile-startup.json");
	auto app = Robin::create_application();
	RB_PROFILE_END_SESSION("startup");
	
	RB_PROFILE_BEGIN_SESSION("runtime", "robin_profile-runtime.json");
	app->run();
	RB_PROFILE_END_SESSION("runtime")

	RB_PROFILE_BEGIN_SESSION("shutdown", "robin_profile-shutdown.json");
	delete app;
	RB_PROFILE_END_SESSION("shutdown");
}

#endif