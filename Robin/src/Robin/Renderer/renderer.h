#pragma once

#include "render_command.h"
#include "camera.h"
#include "shader.h"

namespace Robin
{
	class renderer
	{
	public:
		static void init();
		
		static void begin_scene(perspective_camera& camera);
		static void end_scene();

		static void submit(const ref<shader>& shader, const ref<vertex_array>& vertex_array, const glm::mat4& transform);


		inline static renderer_api::api get_renderer_api() { return renderer_api::get_api(); }

	private:
		struct scene_data
		{
			glm::mat4 view_projection_matrix;
		};

		static scene_data* m_scene_data; 
	};
}