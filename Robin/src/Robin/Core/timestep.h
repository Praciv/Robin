#pragma once

namespace Robin
{
	class timestep
	{
	public:
		timestep(const float time = 0.f)
			: m_time(time)
		{}

		operator float() const { return m_time; }

		float get_seconds() const { return m_time; }
		float get_milliseconds() const { return m_time * 1000.f; }

	private:
		float m_time;
	};
}