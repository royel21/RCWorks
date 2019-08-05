workspace "RCWorks"
    architecture "x64"

    configurations{
        "Release",
        "Debug",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

project "TestingGround"
    location "TestingGround"
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
		"vendor/GLM"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "on"
        systemversion "latest"
    
    filter "configurations:Release"
        defines "P_RELEASE"
        optimize "on"
    
    
    filter "configurations:Debug"
        defines "P_DEBUG"
        symbols "on"
    
    filter "configurations:Dist"
        defines "P_DIST"
        symbols "on"

project "ZombieGame"
    location "ZombieGame"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "./%{prj.name}/vendors/freetype/**.h",
        "./%{prj.name}/vendors/freetype/**.c",
        "./%{prj.name}/vendors/freetype/**.cpp"
    }

    includedirs
    {
        "vendor/spdlog/include",
        "vendor/SDL/include",
        "vendor/GLEW/include",
        "vendor/GLM",
        "./%{prj.name}/vendors/freetype/include",
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
        staticruntime "on"
        systemversion "latest"
        defines
        {
            "GLEW_STATIC"
        }

    filter "configurations:Release"
    defines "P_RELEASE"
    optimize "on"


    filter "configurations:Debug"
    defines "P_DEBUG"
    symbols "on"

    filter "configurations:Dist"
    defines "P_DIST"
    symbols "on"


project "PlutusEngine"
    location "PlutusEngine"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

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
        staticruntime "on"
        systemversion "latest"
        defines
        {
            "GLEW_STATIC",
            "FT2_BUILD_LIBRARY",
            "_CRT_SECURE_NO_WARNINGS"
        }
        
    filter "configurations:Release"
    defines "P_RELEASE"
    optimize "on"


    filter "configurations:Debug"
    defines "P_DEBUG"
    symbols "on"

    filter "configurations:Dist"
    defines "P_DIST"
    symbols "on"
    
    -- filter {"system:windows", "configurations:release"}
    --  buildoptions "/MT"