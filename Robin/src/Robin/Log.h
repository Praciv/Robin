#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Robin 
{
	class ROBIN_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger;  }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

// core log macros
#define RB_CORE_TRACE(...)   ::Robin::Log::get_core_logger()->trace(__VA_ARGS__)
#define RB_CORE_INFO(...)    ::Robin::Log::get_core_logger()->info(__VA_ARGS__)
#define RB_CORE_WARN(...)    ::Robin::Log::get_core_logger()->warn(__VA_ARGS__)
#define RB_CORE_ERROR(...)   ::Robin::Log::get_core_logger()->error(__VA_ARGS__)
#define RB_CORE_FATAL(...)   ::Robin::Log::get_core_logger()->fatal(__VA_ARGS__)

// client log macros
#define RB_TRACE(...)       ::Robin::Log::get_client_logger()->trace(__VA_ARGS__)
#define RB_INFO(...)        ::Robin::Log::get_client_logger()->info(__VA_ARGS__)
#define RB_WARN(...)        ::Robin::Log::get_client_logger()->warn(__VA_ARGS__)
#define RB_ERROR(...)       ::Robin::Log::get_client_logger()->error(__VA_ARGS__)
#define RB_FATAL(...)       ::Robin::Log::get_client_logger()->fatal(__VA_ARGS__)