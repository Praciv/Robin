#include <Robin.h>

#include "imgui/imgui.h"

class example_layer : public Robin::layer
{
public:
	example_layer()
		: layer("example")
	{}

	void on_update() override
	{
		if (Robin::input::is_key_pressed(RB_KEY_TAB))
			RB_TRACE("Tab is pressed");
	}

	void on_event(Robin::event& event) override
	{
		if (event.get_event_type() == Robin::event_type::key_pressed)
		{
			Robin::key_pressed_event& e = (Robin::key_pressed_event&)event;

			RB_TRACE("{0}", (char)e.get_key_code());
		}
	}

	void on_imgui_render() override
	{
		//ImGui::Begin("example");
	}
};

class sandbox : public Robin::application
{
public: 
	sandbox()
	{
		push_layer(new example_layer());
	}

	~sandbox()
	{

	}
};

Robin::application* Robin::create_application()
{
	return new sandbox();
}