#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Robin 
{
	class ROBIN_API log
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
#define RB_CORE_TRACE(...)   ::Robin::log::get_core_logger()->trace(__VA_ARGS__)
#define RB_CORE_INFO(...)    ::Robin::log::get_core_logger()->info(__VA_ARGS__)
#define RB_CORE_WARN(...)    ::Robin::log::get_core_logger()->warn(__VA_ARGS__)
#define RB_CORE_ERROR(...)   ::Robin::log::get_core_logger()->error(__VA_ARGS__)
#define RB_CORE_FATAL(...)   ::Robin::log::get_core_logger()->fatal(__VA_ARGS__)

// client log macros
#define RB_TRACE(...)       ::Robin::log::get_client_logger()->trace(__VA_ARGS__)
#define RB_INFO(...)        ::Robin::log::get_client_logger()->info(__VA_ARGS__)
#define RB_WARN(...)        ::Robin::log::get_client_logger()->warn(__VA_ARGS__)
#define RB_ERROR(...)       ::Robin::log::get_client_logger()->error(__VA_ARGS__)
#define RB_FATAL(...)       ::Robin::log::get_client_logger()->fatal(__VA_ARGS__)