include "./vendor/premake/premake_customization/solution_items.lua"

workspace "RayTracing"
	architecture "x86_64"
	startproject "RayTracing"

	configurations
	{
		"Debug",
		"Release"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
group ""

include "RayTracing"
