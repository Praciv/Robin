workspace "Robin"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directiories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Robin/vendor/GLFW/include"

include "Robin/vendor/GLFW"

project "Robin"
	location "Robin"
	kind "SharedLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rbpch.h"
	pchsource "Robin/src/rbpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		buildoptions 
		{ 
			"/utf-8" 
		}

		defines 
		{
			"RB_PLATFORM_WINDOWS",
			"RB_BUILD_DLL"
		}

		postbuildcommands
		{
			("xcopy \"%{cfg.buildtarget.abspath}\" \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/\" /Y /I /R /F")
		}

	filter "configurations:Debug"
		defines "RB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RB_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Robin/vendor/spdlog/include",
		"Robin/src"
	}

	links
	{
		"Robin"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions 
		{ 
			"/utf-8" 
		}

		defines 
		{
			"RB_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RB_DIST"
		optimize "On" 
