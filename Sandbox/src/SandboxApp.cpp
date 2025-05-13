#include <Robin.h>

class Sandbox : public Robin::Application
{
public: 
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Robin::Application* Robin::create_application()
{
	return new Sandbox();
}