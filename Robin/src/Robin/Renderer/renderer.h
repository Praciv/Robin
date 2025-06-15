#pragma once

#include "Robin/Renderer/render_command.h"
#include "Robin/camera_controller.h"
#include "Robin/Renderer/shader.h"

namespace Robin
{
	class renderer
	{
	public:
		static void init();
		
		static void begin_scene(perspective_camera_controller& camera);
		static void end_scene();

		void submit_scene(const ref<shader>& shader, const ref<vertex_array>& vertex_array);

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