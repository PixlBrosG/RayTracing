#pragma once

#include "RayTracing/Core/Base.h"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace RayTracing {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static Ref<spdlog::logger> s_Logger;
	};

}

#define RT_TRACE(...)      ::RayTracing::Log::GetLogger()->trace(__VA_ARGS__)
#define RT_INFO(...)       ::RayTracing::Log::GetLogger()->info(__VA_ARGS__)
#define RT_WARN(...)       ::RayTracing::Log::GetLogger()->warn(__VA_ARGS__)
#define RT_ERROR(...)      ::RayTracing::Log::GetLogger()->error(__VA_ARGS__)
#define RT_CRITICAL(...)   ::RayTracing::Log::GetLogger()->critical(__VA_ARGS__)
