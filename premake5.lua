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
IncludeDir["GLAD"] = "Robin/vendor/GLAD/include"
IncludeDir["ImGui"] = "Robin/vendor/imgui"
IncludeDir["glm"] = "Robin/vendor/glm"


include "Robin/vendor/GLFW"
include "Robin/vendor/GLAD"
include "Robin/vendor/imgui"


project "Robin"
	location "Robin"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rbpch.h"
	pchsource "Robin/src/rbpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0"

		defines 
		{
			"RB_PLATFORM_WINDOWS",
			"RB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("xcopy \"%{cfg.buildtarget.abspath}\" \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/\" /Y /I /R /F")
		}

	filter "configurations:Debug"
		defines "RB_DEBUG"
		symbols "On"
		runtime "Debug"
		buildoptions "/utf-8"

	filter "configurations:Release"
		defines "RB_RELEASE"
		optimize "On"
		runtime "Release"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "RB_DIST"
		optimize "On"
		runtime "Release"
		buildoptions "/utf-8"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Robin/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Robin"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"RB_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RB_DEBUG"
		symbols "On"
		runtime "Debug"
		buildoptions "/utf-8"

	filter "configurations:Release"
		defines "RB_RELEASE"
		optimize "On"
		runtime "Release"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "RB_DIST"
		optimize "On" 
		runtime "Release"
		buildoptions "/utf-8"