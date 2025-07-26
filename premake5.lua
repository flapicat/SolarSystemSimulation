workspace "SolarSimulation"
	architecture "x64"
	startproject "SolarSimulation"

	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "SolarSimulation/vendor/GLFW/include"
IncludeDir["Glad"] = "SolarSimulation/vendor/Glad/include"
IncludeDir["ImGui"] = "SolarSimulation/vendor/imgui"
IncludeDir["glm"] = "SolarSimulation/vendor/glm"

group "Dependencies"
	include "SolarSimulation/vendor/GLFW"
	include "SolarSimulation/vendor/Glad"
	include "SolarSimulation/vendor/imgui"
	include "SolarSimulation/vendor/glm"
group ""

project "SolarSimulation"
	location "SolarSimulation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"glm",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
