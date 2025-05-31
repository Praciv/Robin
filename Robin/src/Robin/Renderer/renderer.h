#pragma once

namespace Robin
{
	enum class renderer_API
	{
		none = 0, opengl = 1
	};

	class renderer
	{
	public:
		inline static renderer_API get_renderer_api() { return s_renderer_API; }
	private:
		static renderer_API s_renderer_API;
	};
}