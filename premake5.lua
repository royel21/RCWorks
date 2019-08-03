workspace "RCWorks"
    architecture "x64"

    configurations{
        "Release",
        "Debug",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

project "PlutusEngine"
    location "PlutusEngine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "vendor/spdlog/include",
        "vendor/SDL/include",
        "vendor/GLEW/include",
		"vendor/GLM"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "GLEW_STATIC"
        }
        
    filter "configurations:Release"
    defines "P_RELEASE"
    optimize "On"


    filter "configurations:Debug"
    defines "P_DEBUG"
    symbols "On"

    filter "configurations:Dist"
    defines "P_DIST"
    symbols "On"
    
    -- filter {"system:windows", "configurations:release"}
    --  buildoptions "/MT"
project "ZombieGame"
    location "ZombieGame"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "vendor/spdlog/include",
        "vendor/SDL/include",
        "vendor/GLEW/include",
		"vendor/GLM",
		"./"
    }

    links
    {
        "PlutusEngine",
		"SDL2.lib",
		"SDL2main.lib",
		"glew32s.lib",
		"opengl32.lib"
    }
	libdirs { 
		"vendor/GLEW/lib/x64", 
        "vendor/SDL/lib/x64"
	}

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "GLEW_STATIC"
        }

    filter "configurations:Release"
    defines "P_RELEASE"
    optimize "On"


    filter "configurations:Debug"
    defines "P_DEBUG"
    symbols "On"

    filter "configurations:Dist"
    defines "P_DIST"
    symbols "On"