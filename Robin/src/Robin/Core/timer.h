#pragma once
#include "rbpch.h"

#include <memory>
#include <chrono>

namespace Robin
{
	class timer_manager
	{
	private:
		struct sample
		{
			std::string name;
			float duration_ms;
		};

		struct profile_average {
			float total_time = 0.f;
			int sample_count = 0;
			std::string name;
		};
	public:
		timer_manager() {}

		void record_sample(const std::string& name, float duration_ms)
		{
			m_current_frame_data.push_back({name, duration_ms});

			m_averaging_buffer[name].total_time += duration_ms;
			m_averaging_buffer[name].sample_count++;
			m_averaging_buffer[name].name = name;
		}

		void end_frame()
		{
			m_current_averaging_frame++;

			if (m_current_averaging_frame >= m_averaging_frame_count)
			{
				m_display_data.clear();

				for (auto& [name, average] : m_averaging_buffer)
				{
					if (average.sample_count > 0)
					{
						float average_time = average.total_time / average.sample_count;
						m_display_data.push_back({ name, average_time });
					}
				}

				m_averaging_buffer.clear();
				m_current_averaging_frame = 0;
			}
			//m_display_data = std::move(m_current_frame_data);
			//m_current_frame_data.clear();
		}

		const std::vector<sample>& get_sample_data() { return m_display_data; }
		const std::unordered_map<std::string, profile_average>& get_display_data() { return m_averaging_buffer; }
		//const float get_average(const std::string& name) { return ; }

		inline static scope<timer_manager>& get_instance() { return s_manager; }

	private:

		static scope<timer_manager> s_manager; 

		std::vector<sample> m_current_frame_data;
		std::vector<sample> m_display_data;

		std::unordered_map<std::string, profile_average> m_averaging_buffer;
		int m_averaging_frame_count = 10; 
		int m_current_averaging_frame = 0;

	};

	class timer
	{
	public:
		timer(const std::string& name)
		{
			m_name = name; 
			m_start_time = std::chrono::high_resolution_clock::now();
		}

		~timer()
		{
			stop();
		}

		void stop()
		{
			auto end_time_point = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration<float, std::micro>(end_time_point - m_start_time);

			timer_manager::get_instance()->record_sample(m_name, duration.count());
		}

	private:
		std::string m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time; 
	};
}