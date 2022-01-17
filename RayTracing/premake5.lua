project "RayTracing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.glm}"
	}

	filter "system:Windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "RT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RT_RELEASE"
		runtime "Release"
		optimize "on"
