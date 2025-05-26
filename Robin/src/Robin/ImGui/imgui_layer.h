#pragma once

#include "Robin/layer.h"

#include "Robin/Events/mouse_event.h"
#include "Robin/Events/key_event.h"
#include "Robin/Events/application_event.h"

namespace Robin
{
	class ROBIN_API imgui_layer : public layer
	{
	public:
		imgui_layer();
		~imgui_layer();

		void on_attach() override;
		void on_detach() override;
		void on_imgui_render() override;


		void begin();
		void end();

	private:
		float m_time = 0.f;
	};
}