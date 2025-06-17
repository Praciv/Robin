#pragma once
#include "rbpch.h"

#include <memory>
#include <chrono>

namespace Robin
{
	struct profile_result
	{
		const char* name;
		long long start, end;
	};

	struct instrumentation_session
	{
		const char* name;

		instrumentation_session(const char* name)
			: name(name)
		{
		}
	};

	class instrumentor
	{
	private:
		instrumentation_session* m_current_session; 
		std::ofstream m_output_stream;
		int m_profile_count;
	public: 
		instrumentor()
			:	m_current_session(nullptr), m_profile_count(0)
		{
		}

		void begin_session(const char* name, const std::string& file_path = "results.json")
		{
			m_output_stream.open(file_path);
			write_header();
			m_current_session = new instrumentation_session(name);
		}

		void end_session()
		{
			write_footer();
			m_output_stream.close();
			delete m_current_session; 
			m_current_session = nullptr;
			m_profile_count = 0;
		}

		void write_profile(const profile_result& result)
		{
			if (m_profile_count++ > 0)
				m_output_stream << ",";

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_output_stream << "{";
			m_output_stream << "\"cat\":\"function\",";
			m_output_stream << "\"dur\":" << (result.end - result.start) << ',';
			m_output_stream << "\"name\":\"" << name << "\",";
			m_output_stream << "\"ph\":\"X\",";
			m_output_stream << "\"pid\":0,";
			m_output_stream << "\"ts\":" << result.start;
			m_output_stream << "}";

		}

		void write_header()
		{
			m_output_stream << "{\"otherData\": {},\"traceEvents\":[";
			m_output_stream.flush();
		}

		void write_footer()
		{
			m_output_stream << "]}";
			m_output_stream.flush();
		}

		static instrumentor& get()
		{
			static instrumentor instance; 
			return instance; 
		}
	};

	class instrumentor_timer
	{
	public:
		instrumentor_timer(const char* name)
			:	m_name(name), m_start_time(std::chrono::high_resolution_clock::now()), m_stopped(false)
		{
		}

		~instrumentor_timer()
		{
			if(!m_stopped)
				stop();
		}

		void stop()
		{
			auto end_time_point = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration<float, std::micro>(end_time_point - m_start_time);

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

			instrumentor::get().write_profile({ m_name, start, end });
			m_stopped = true; 
		}

	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
		bool m_stopped;
	};
}