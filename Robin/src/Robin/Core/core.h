#pragma once

#include <functional>
#include <memory>

#ifdef RB_PLATFORM_WINDOWS
	#if RB_DYNAMIC_LINK
		#ifdef RB_BUILD_DLL
			#define ROBIN_API __declspec(dllexport)
		#else
			#define	ROBIN_API __declspec(dllimport)	
		#endif
	#else 
		#define ROBIN_API	
	#endif
#else
	#error Robin only supports windows
#endif 

#ifdef RB_DEBUG
	#define RB_ENABLE_ASSERTS
	#define RB_PROFILING_ENABLED
#endif

#ifdef RB_ENABLE_ASSERTS
	#define RB_ASSERT(x, ...) { if(!(x)) { RB_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RB_CORE_ASSERT(x, ...) { if(!(x)) { RB_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RB_ASSERT(x, ...) 
	#define RB_CORE_ASSERT(x, ...)
#endif

#ifdef RB_PROFILING_ENABLED
	#define RB_PROFILE_FUNCTION() timer profiler(__FUNCTION__)
	#define RB_PROFILE_SCOPE(name) timer profiler(name)
#else
	#define RB_PROFILE_FUNCTION()
	#define RB_PROFILE_SCOPE(name)
#endif


#define BIT(x) (1 << x)

#define RB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Robin
{
	template<typename T> 
	using scope = std::unique_ptr<T>;

	template<typename T>
	using ref = std::shared_ptr<T>;
}