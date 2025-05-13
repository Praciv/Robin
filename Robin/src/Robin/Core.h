#pragma once

#ifdef RB_PLATFORM_WINDOWS
	#ifdef RB_BUILD_DLL
		#define ROBIN_API __declspec(dllexport)
	#else
		#define	ROBIN_API __declspec(dllimport)	
	#endif
#else
	#error Robin only supports windows
#endif 
