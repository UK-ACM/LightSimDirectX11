
-- defines our entire workspace as our solution in VS
workspace "DX11Basics"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	startproject "DX11Basics"


-- Defines the main output dir for files 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "DX11Basics"
	location "DX11Basics"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

	}

	includedirs {
		"%{prj.name}/src",
	}


	filter "system:windows"
		systemversion "latest"

		characterset("MBCS")
		floatingpoint "Fast"

	filter "configurations:Debug"
		defines "OA_DEBUG"
		runtime "Debug"
		symbols "on"
		optimize "Debug"

	filter "configurations:Release"
		defines "OA_RELEASE"
		runtime "Release"
		optimize "Speed"

	filter "configurations:Dist"
		defines "OA_DIST"
		runtime "Release"
		optimize "Speed"




