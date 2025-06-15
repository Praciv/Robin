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
IncludeDir["stb_image"] = "Robin/vendor/stb_image"

include "Robin/vendor/GLFW"
include "Robin/vendor/GLAD"
include "Robin/vendor/imgui"


project "Robin"
	location "Robin"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rbpch.h"
	pchsource "Robin/src/rbpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
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
		systemversion "10.0"

		defines 
		{
			"RB_PLATFORM_WINDOWS",
			"RB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RB_DEBUG"
		symbols "on"
		runtime "Debug"
		buildoptions "/utf-8"

	filter "configurations:Release"
		defines "RB_RELEASE"
		optimize "on"
		runtime "Release"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "RB_DIST"
		optimize "on"
		runtime "Release"
		buildoptions "/utf-8"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Robin/src",
		"%{IncludeDir.glm}",
		"Robin/vendor"
	}

	links
	{
		"Robin"
	}

	filter "system:windows"
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

project "Robin-Editor"
	location "Robin-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Robin/src",
		"%{IncludeDir.glm}",
		"Robin/vendor"
	}

	links
	{
		"Robin"
	}

	filter "system:windows"
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