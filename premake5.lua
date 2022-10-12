
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
		"%{prj.name}/src/**.inl",
		"%{prj.name}/shaders/**.hlsl"


	}

	includedirs {
		"%{prj.name}/src",
	}

	shadermodel("5.0")
	shaderassembler("AssemblyCode")
   local shader_dir = "shaders/"
 
   -- HLSL files that don't end with 'Extensions' will be ignored as they will be
   -- used as includes
   filter("files:**.hlsl")
     flags("ExcludeFromBuild")
     shaderobjectfileoutput(shader_dir.."%{file.basename}"..".cso")
     shaderassembleroutput(shader_dir.."%{file.basename}"..".asm")
 
   filter("files:**_ps.hlsl")
     removeflags("ExcludeFromBuild")
     shadertype("Pixel")
 
   filter("files:**_vs.hlsl")
      removeflags("ExcludeFromBuild")
      shadertype("Vertex")
 
 
   -- Warnings as errors
   shaderoptions({"/WX"})


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




