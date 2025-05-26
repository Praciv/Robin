#pragma once

#include "Robin/core.h"
#include "Robin/Events/event.h"

namespace Robin
{
	class ROBIN_API layer
	{
	public: 
		layer(const std::string& name = "layer");
		virtual ~layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_imgui_render() {}
		virtual void on_event(event& event) {}

		inline const std::string& get_name() const { return m_debug_name;  }
	protected: 
		std::string m_debug_name;
	};
}