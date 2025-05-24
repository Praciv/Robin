#include <Robin.h>

class example_layer : public Robin::layer
{
public:
	example_layer()
		: layer("example")
	{}

	void on_update() override
	{

	}

	void on_event(Robin::event& event) override
	{

	}
};

class sandbox : public Robin::application
{
public: 
	sandbox()
	{
		push_layer(new example_layer());
		push_overlay(new Robin::imgui_layer());
	}

	~sandbox()
	{

	}
};

Robin::application* Robin::create_application()
{
	return new sandbox();
}