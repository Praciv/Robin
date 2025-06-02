#include "rbpch.h"
#include "render_command.h"

#include "Platform/OpenGL/opengl_renderer_api.h"

namespace Robin
{
	renderer_api* render_command::s_renderer_api = new opengl_renderer_api;
}